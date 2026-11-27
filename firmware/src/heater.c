#include "t90b.h"

#if T90B_HEAT_PROBE
#define HEATER_DUTY_LIMIT_PCT T90B_HEAT_PROBE_MAX_DUTY
#define HEAT_PROBE_CUTOFF_C 100
#define HEAT_PROBE_TARGET_C 100
#else
#define HEATER_DUTY_LIMIT_PCT 20U
#endif

#if T90B_HEAT_TOGGLE_TEST
/* PID gains use thousandths of a PWM percentage point. */
#define PID_SCALE          1000
#define PID_KP             2000
#define PID_KI_PER_SEC      100
#define PID_KD_SECONDS      100
#define PID_D_FILTER_MS     750
#define PID_LIMIT          ((int32_t)HEATER_DUTY_LIMIT_PCT * PID_SCALE)
#define PID_I_DIVISOR      (10000 / PID_KI_PER_SEC)
#define PID_INTEGRAL_LIMIT (8 * PID_SCALE * PID_I_DIVISOR)
/* Forecast 1.5 s at up to 2 C/s, extending to 3 s at 5 C/s. */
#define PID_LOOKAHEAD_MIN_MS 1500
#define PID_LOOKAHEAD_MAX_MS 3000
#define PID_SLOW_RATE        2
#define PID_FAST_RATE        5
#define PID_TAPER_PER_C      30
#define PID_FINE_BAND_DC   20
#define PID_BOOST_KP       30000
#define THERMAL_TRIP_MARGIN_DC 50
#define RISE_CHECK_MS      12000U
#define RISE_MIN_DC        20
#define RISE_CHECK_DUTY    60U
#define PID_HOLD_BIAS      (9 * PID_SCALE)

static int32_t pid_request(heater_ctrl_t *ctrl, int32_t error_dc,
                           int16_t actual_dc, int32_t hold_bias, uint32_t now_ms) {
    int32_t proportional = error_dc * (PID_KP / 10);
    if (error_dc > PID_FINE_BAND_DC) {
        proportional += (error_dc - PID_FINE_BAND_DC) * (PID_BOOST_KP / 10);
    }
    if (!ctrl->pid_started) {
        ctrl->pid_started = true;
        ctrl->pid_sample_ms = now_ms;
        ctrl->pid_previous_dc = actual_dc;
        ctrl->pid_integral = 0;
        ctrl->pid_derivative = 0;
    }
    const uint32_t elapsed_ms = now_ms - ctrl->pid_sample_ms;
    const bool new_sample = elapsed_ms > 0U && elapsed_ms <= T90B_SENSOR_TIMEOUT_MS;
    if (new_sample) {
        const int32_t dt = (int32_t)elapsed_ms;
        int32_t change_dc = (int32_t)actual_dc - ctrl->pid_previous_dc;
        if (change_dc > 5120) {
            change_dc = 5120;
        } else if (change_dc < -5120) {
            change_dc = -5120;
        }
        int32_t derivative = (PID_D_FILTER_MS * ctrl->pid_derivative -
                              (PID_KD_SECONDS * (PID_SCALE / 10)) * change_dc) /
                             (PID_D_FILTER_MS + dt);
        if (derivative > PID_LIMIT) {
            derivative = PID_LIMIT;
        } else if (derivative < -PID_LIMIT) {
            derivative = -PID_LIMIT;
        }
        ctrl->pid_derivative = derivative;
        ctrl->pid_sample_ms = now_ms;
        ctrl->pid_previous_dc = actual_dc;
    }

    /* The derivative is negative while heating. Allow the stored heat to coast. */
    const int32_t rise = ctrl->pid_derivative < 0 ? -ctrl->pid_derivative : 0;
    int32_t lookahead_ms = PID_LOOKAHEAD_MIN_MS;
    if (rise >= PID_FAST_RATE * PID_KD_SECONDS) {
        lookahead_ms = PID_LOOKAHEAD_MAX_MS;
    } else if (rise > PID_SLOW_RATE * PID_KD_SECONDS) {
        lookahead_ms += (rise - PID_SLOW_RATE * PID_KD_SECONDS) *
                        (PID_LOOKAHEAD_MAX_MS - PID_LOOKAHEAD_MIN_MS) /
                        ((PID_FAST_RATE - PID_SLOW_RATE) * PID_KD_SECONDS);
    }
    const int32_t projected_rise = rise * lookahead_ms / PID_KD_SECONDS;
    const int32_t headroom = error_dc * (PID_SCALE / 10) -
                             projected_rise;
    int32_t ceiling = 0;
    if (error_dc > 0) {
        ceiling = hold_bias + headroom * PID_TAPER_PER_C;
        if (ceiling < 0) {
            ceiling = 0;
        } else if (ceiling > PID_LIMIT) {
            ceiling = PID_LIMIT;
        }
    }

    const int32_t pd = proportional + ctrl->pid_derivative + hold_bias;
    if (new_sample) {
        int32_t integral = ctrl->pid_integral +
                           error_dc * (int32_t)elapsed_ms;
        if (integral < 0) {
            integral = 0;
        } else if (integral > PID_INTEGRAL_LIMIT) {
            integral = PID_INTEGRAL_LIMIT;
        }
        if (integral <= ctrl->pid_integral || pd + integral / PID_I_DIVISOR <= ceiling) {
            ctrl->pid_integral = integral;
        }
    }
    const int32_t request = pd + ctrl->pid_integral / PID_I_DIVISOR;
    return (request > ceiling ? ceiling : request) / PID_SCALE;
}
#endif

void heater_init(heater_ctrl_t *ctrl) {
    if (!ctrl) {
        return;
    }
    ctrl->armed = false;
    ctrl->tripped = false;
    ctrl->last_sensor_ms = 0U;
    ctrl->trip_reason = FAULT_NONE;
    ctrl->duty_pct = 0U;
#if T90B_HEAT_TOGGLE_TEST
    ctrl->pid_started = false;
#endif
#if T90B_HEAT_PRESETS
    ctrl->cooldown_low_dc = 0;
#endif
    board_set_heater_pwm(0U);
}

void heater_trip(heater_ctrl_t *ctrl, uint32_t reason) {
    if (!ctrl) {
        return;
    }
    ctrl->armed = false;
    ctrl->tripped = true;
    ctrl->trip_reason |= reason;
    ctrl->duty_pct = 0U;
#if T90B_HEAT_TOGGLE_TEST
    ctrl->pid_started = false;
#endif
    board_set_heater_pwm(0U);
}

bool heater_rearm(heater_ctrl_t *ctrl, uint32_t faults, bool sensor_valid, uint32_t now_ms) {
    if (!ctrl) {
        return false;
    }
    if (faults != FAULT_NONE || !sensor_valid) {
        return false;
    }
    ctrl->tripped = false;
    ctrl->trip_reason = FAULT_NONE;
    ctrl->armed = true;
#if T90B_HEAT_TOGGLE_TEST
    ctrl->checking_rise = false;
#elif T90B_HEAT_PROBE
    ctrl->armed_since_ms = now_ms;
#endif
    ctrl->last_sensor_ms = now_ms;
    return true;
}

/* Check the previous sample before accepting a replacement after a stall. */
void heater_record_sample(heater_ctrl_t *ctrl, uint32_t faults, uint32_t now_ms) {
    if (faults != FAULT_NONE) {
        heater_trip(ctrl, faults);
        return;
    }
    if (ctrl->armed && now_ms - ctrl->last_sensor_ms > T90B_SENSOR_TIMEOUT_MS) {
        heater_trip(ctrl, FAULT_SENSOR);
        return;
    }
    ctrl->last_sensor_ms = now_ms;
}

uint8_t heater_step(heater_ctrl_t *ctrl, bool heat_requested, int16_t target_c,
                    int16_t actual_dc, uint32_t faults, uint32_t now_ms) {
    if (!ctrl) {
        return 0U;
    }
    if (faults != FAULT_NONE) {
        heater_trip(ctrl, faults);
        return 0U;
    }
    if (ctrl->armed && now_ms - ctrl->last_sensor_ms > T90B_SENSOR_TIMEOUT_MS) {
        heater_trip(ctrl, FAULT_SENSOR);
        return 0U;
    }
    if (ctrl->tripped || !ctrl->armed || !heat_requested) {
        ctrl->duty_pct = 0U;
#if T90B_HEAT_TOGGLE_TEST
        ctrl->pid_started = false;
#endif
        board_set_heater_pwm(0U);
        return 0U;
    }
    const int32_t error_dc = (int32_t)target_c * 10 - actual_dc;
#if T90B_HEAT_TOGGLE_TEST
    /* Scale the 100 C holding estimate with heat loss to a nominal 25 C room. */
    const int32_t hold_bias = PID_HOLD_BIAS * (target_c - 25) / 75;
    const int32_t requested_pct = pid_request(ctrl, error_dc, actual_dc, hold_bias, now_ms);
#else
    const int32_t requested_pct = (error_dc / 10) * 2;
#endif
    if (requested_pct <= 0) {
        ctrl->duty_pct = 0U;
    } else if (requested_pct > (int32_t)HEATER_DUTY_LIMIT_PCT) {
        ctrl->duty_pct = HEATER_DUTY_LIMIT_PCT;
    } else {
        ctrl->duty_pct = (uint8_t)requested_pct;
    }
#if T90B_HEATER_ENABLED
    board_set_heater_pwm(ctrl->duty_pct);
#else
    board_set_heater_pwm(0U);
#endif
    return ctrl->duty_pct;
}


void heater_ui_step(heater_ctrl_t *ctrl, t90b_state_t *ui, uint32_t now_ms,
                    btn_event_t btn_a, btn_event_t btn_b) {
#if T90B_HEAT_PRESETS
    const int16_t target_c = (int16_t)ui->preset_c;
#elif T90B_HEAT_PROBE
    const int16_t target_c = HEAT_PROBE_TARGET_C;
#endif
    const bool was_armed = ctrl->armed;
    const bool start_requested = ui->screen == UI_SCREEN_STANDBY &&
                                 btn_a == BTN_SHORT && btn_b == BTN_NONE;
#if T90B_HEAT_TOGGLE_TEST
    /* Check the response to the previous command before issuing the next one. */
    if (ctrl->armed && ctrl->duty_pct >= RISE_CHECK_DUTY && ui->faults == FAULT_NONE) {
        if (!ctrl->checking_rise || ui->tip_temp_dc >= ctrl->rise_start_dc + RISE_MIN_DC) {
            ctrl->checking_rise = true;
            ctrl->rise_start_dc = ui->tip_temp_dc;
            ctrl->rise_start_ms = now_ms;
        } else if (now_ms - ctrl->rise_start_ms >= RISE_CHECK_MS) {
            ui->faults |= FAULT_THERMAL;
        }
    } else {
        ctrl->checking_rise = false;
    }
    int32_t trip_dc = target_c * 10 + THERMAL_TRIP_MARGIN_DC;
#if T90B_HEAT_PRESETS
    if (next_heat_preset(ui->preset_c) == 0U) {
        ui->faults |= FAULT_SENSOR;
    }
    if (start_requested) {
        ctrl->cooldown_low_dc = ui->tip_temp_dc;
    }
    if (ctrl->cooldown_low_dc > target_c * 10) {
        /* Track cooling after starting with heat left over from a higher preset. */
        if (ui->tip_temp_dc < ctrl->cooldown_low_dc) {
            ctrl->cooldown_low_dc = ui->tip_temp_dc;
        }
        if (ctrl->cooldown_low_dc > target_c * 10) {
            trip_dc = ctrl->cooldown_low_dc + THERMAL_TRIP_MARGIN_DC;
            const int32_t max_trip_dc = T90B_PRESET_MAX_C * 10 + THERMAL_TRIP_MARGIN_DC;
            if (trip_dc > max_trip_dc) {
                trip_dc = max_trip_dc;
            }
        }
    }
#endif
    if (ui->tip_temp_dc >= trip_dc && (ctrl->armed || start_requested)) {
        ui->faults |= FAULT_THERMAL;
    }
    if (ctrl->trip_reason & FAULT_THERMAL) {
        if (btn_a == BTN_SHORT && btn_b == BTN_NONE &&
            ui->tip_temp_dc < target_c * 10 && ui->faults == FAULT_NONE) {
            ctrl->trip_reason &= ~FAULT_THERMAL;
            btn_a = BTN_NONE; /* Acknowledge. A separate press starts heating. */
        } else {
            ui->faults |= FAULT_THERMAL;
        }
    }
#endif
    heater_record_sample(ctrl, ui->faults, now_ms);
    if (was_armed && !ctrl->armed && ui->faults == FAULT_NONE) {
        ui->faults = FAULT_SENSOR;
    }

#if T90B_HEAT_TOGGLE_TEST
    if (ctrl->armed && btn_a == BTN_SHORT && btn_b == BTN_NONE) {
        ctrl->armed = false;
        ui->screen = UI_SCREEN_STANDBY;
        btn_a = BTN_NONE;
    }
#endif
    ui_step(ui, now_ms, btn_a, btn_b);
    if (start_requested && ui->screen == UI_SCREEN_MAIN_HEAT) {
        heater_rearm(ctrl, ui->faults, ui->faults == FAULT_NONE, now_ms);
    }
#if T90B_HEAT_PROBE && !T90B_HEAT_TOGGLE_TEST
    if (ctrl->armed && (now_ms - ctrl->armed_since_ms >= T90B_HEAT_PROBE_DURATION_MS ||
                        ui->tip_temp_dc >= HEAT_PROBE_CUTOFF_C * 10)) {
        ctrl->armed = false;
        ui->screen = UI_SCREEN_STANDBY;
    }
#endif
    const bool heat_requested = ui->screen == UI_SCREEN_MAIN_HEAT ||
                                ui->screen == UI_SCREEN_SETPOINT ||
                                ui->screen == UI_SCREEN_SLEEP;
    if (!heat_requested) {
        ctrl->armed = false;
    }
#if !T90B_HEAT_PROBE
    const int16_t target_c = (int16_t)(ui->screen == UI_SCREEN_SLEEP
                                      ? ui->prefs.sleep_temp_c
                                      : ui->prefs.setpoint_c);
#endif
    ui->heater_duty_pct = heater_step(ctrl, heat_requested, target_c,
                                      ui->tip_temp_dc, ui->faults, now_ms);
}
