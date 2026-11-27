#include "t90b.h"

#if T90B_HEAT_PRESETS
static const uint16_t heat_presets[] = {100U, 200U, 300U, 350U, T90B_PRESET_MAX_C};

uint16_t next_heat_preset(uint16_t current_c) {
    const unsigned count = sizeof(heat_presets) / sizeof(heat_presets[0]);
    for (unsigned i = 0; i < count; ++i) {
        if (heat_presets[i] == current_c) {
            return heat_presets[i + 1U < count ? i + 1U : 0U];
        }
    }
    return 0U;
}
#endif

static const char *const k_menu_labels[16] = {
    "0.Exit",
    "1.Vol Info",
    "2.Temp Step",
    "3.Temp Preset",
    "4.Sleep Temp",
    "5.Sleep Time",
    "6.Stdby Time",
    "7.Work Vol",
    "8.Power trim",
    "9.Temp Unit",
    "10.Language",
    "11.Rota 180",
    "12.P_O Heat",
    "13.Temp Calib",
    "14.Restore",
    "15.Ver Info"
};

const char *ui_menu_label(uint8_t index) {
    if (index >= 16U) {
        return "";
    }
    return k_menu_labels[index];
}

void prefs_load_defaults(t90b_prefs_t *prefs) {
    if (!prefs) {
        return;
    }
    prefs->setpoint_c    = T90B_TEMP_DEFAULT_C;
    prefs->sleep_temp_c  = T90B_SLEEP_TEMP_C;
    prefs->temp_step_c   = 5U;
    prefs->temp_unit     = TEMP_UNIT_C;
    prefs->language      = 0U;
    prefs->rotate_180    = 0U;
    prefs->power_on_heat = 0U;
    prefs->sleep_time_s  = 180U;
    prefs->stdby_time_s  = 180U;
    prefs->work_vol_mv   = 20000U;
    prefs->power_trim    = 0;
    prefs->temp_calib_c  = 0;
}

uint32_t prefs_checksum_u8(const uint8_t *buf, uint32_t len) {
    uint32_t sum = 0U;
    uint32_t i;
    if (!buf || len <= 4U) {
        return 0U;
    }
    for (i = 4U; i < len; i++) {
        sum = (sum + buf[i]) & 0xFFU;
    }
    return sum;
}

bool prefs_validate_block(const uint8_t *buf, uint32_t len) {
    uint32_t stored;
    if (!buf || len <= 4U) {
        return false;
    }
    stored = (uint32_t)buf[0]
           | ((uint32_t)buf[1] << 8)
           | ((uint32_t)buf[2] << 16)
           | ((uint32_t)buf[3] << 24);
    return stored == prefs_checksum_u8(buf, len);
}

bool prefs_save(const t90b_prefs_t *prefs) {
    /* Never write to factory calibration area; actual flash write is gated to bench. */
    return prefs != 0;
}

static void ui_enter(t90b_state_t *state, ui_screen_t screen, uint32_t now_ms) {
    state->screen = screen;
    state->screen_entered_ms = now_ms;
}

void ui_init(t90b_state_t *state, uint8_t factory_flag, const t90b_prefs_t *initial_prefs) {
    if (!state) {
        return;
    }
    state->now_ms = 0U;
    state->screen_entered_ms = 0U;
    state->last_activity_ms = 0U;
    state->menu_index = 0U;
    state->menu_editing = false;
    state->factory_flag = factory_flag;
    state->faults = FAULT_NONE;
    state->tip_temp_dc = 250;
    state->vin_mv = 20000U;
    state->motion_detected = false;
    state->heater_duty_pct = 0U;

    if (initial_prefs) {
        state->prefs = *initial_prefs;
    } else {
        prefs_load_defaults(&state->prefs);
    }
    state->edit_prefs = state->prefs;
#if T90B_HEAT_PRESETS
    state->preset_c = heat_presets[0];
#endif

    if (factory_flag != T90B_PREFS_MAGIC_OK) {
        state->screen = UI_SCREEN_FACTORY;
    } else {
        state->screen = UI_SCREEN_BOOT_LOGO;
    }
}

static void adjust_setpoint(t90b_state_t *state, int16_t delta) {
    int32_t next = (int32_t)state->prefs.setpoint_c + delta;
    if (next < T90B_TEMP_MIN_C) {
        next = T90B_TEMP_MIN_C;
    }
    if (next > T90B_TEMP_MAX_C) {
        next = T90B_TEMP_MAX_C;
    }
    state->prefs.setpoint_c = (uint16_t)next;
}

void ui_step(t90b_state_t *state, uint32_t now_ms, btn_event_t btn_a, btn_event_t btn_b) {
    bool any_btn = (btn_a != BTN_NONE) || (btn_b != BTN_NONE);
    uint32_t stdby_ms;

    if (!state) {
        return;
    }
    state->now_ms = now_ms;
    if (any_btn || state->motion_detected) {
        state->last_activity_ms = now_ms;
    }

    /* Faults override active heating/standby/sleep screens (except factory test). */
    if (state->screen != UI_SCREEN_FACTORY && state->faults != FAULT_NONE) {
        state->heater_duty_pct = 0U;
        if (state->screen != UI_SCREEN_FAULT) {
            ui_enter(state, UI_SCREEN_FAULT, now_ms);
        }
        return;
    }

    if (state->screen == UI_SCREEN_FAULT && state->faults == FAULT_NONE) {
        ui_enter(state, UI_SCREEN_STANDBY, now_ms);
        return;
    }

    switch (state->screen) {
    case UI_SCREEN_FACTORY:
        if (btn_a != BTN_NONE && btn_b != BTN_NONE) {
            state->factory_flag = T90B_PREFS_MAGIC_OK;
            ui_enter(state, UI_SCREEN_BOOT_LOGO, now_ms);
        }
        break;

    case UI_SCREEN_BOOT_LOGO:
        if ((btn_a != BTN_NONE && btn_b != BTN_NONE) ||
            (now_ms - state->screen_entered_ms) >= T90B_BOOT_LOGO_MS) {
            ui_enter(state, UI_SCREEN_STANDBY, now_ms);
        }
        break;

    case UI_SCREEN_STANDBY:
        state->heater_duty_pct = 0U;
        if (btn_a == BTN_SHORT && btn_b == BTN_SHORT) {
            state->edit_prefs = state->prefs;
            state->menu_index = 0U;
            state->menu_editing = false;
            ui_enter(state, UI_SCREEN_MENU, now_ms);
#if T90B_HEAT_PRESETS
        } else if (btn_a == BTN_NONE && btn_b == BTN_SHORT) {
            state->preset_c = next_heat_preset(state->preset_c);
#endif
        } else if (btn_a == BTN_SHORT && btn_b == BTN_NONE) {
            ui_enter(state, UI_SCREEN_MAIN_HEAT, now_ms);
        }
        break;

    case UI_SCREEN_MAIN_HEAT:
        if (btn_a == BTN_SHORT && btn_b == BTN_SHORT) {
            state->edit_prefs = state->prefs;
            state->menu_index = 0U;
            state->menu_editing = false;
            ui_enter(state, UI_SCREEN_MENU, now_ms);
            break;
        }
        if (btn_a == BTN_LONG) {
            ui_enter(state, UI_SCREEN_STANDBY, now_ms);
            break;
        }
#if !T90B_HEAT_PRESETS
        if (btn_a == BTN_SHORT || btn_b == BTN_SHORT) {
            ui_enter(state, UI_SCREEN_SETPOINT, now_ms);
            break;
        }
#endif
#if !T90B_HEAT_TOGGLE_TEST
        const uint32_t sleep_ms = (uint32_t)state->prefs.sleep_time_s * 1000U;
        if (sleep_ms > 0U && (now_ms - state->last_activity_ms) >= sleep_ms) {
            ui_enter(state, UI_SCREEN_SLEEP, now_ms);
        }
#endif
        break;

    case UI_SCREEN_SETPOINT:
        if (btn_a == BTN_SHORT) {
            adjust_setpoint(state, -(int16_t)state->prefs.temp_step_c);
            state->screen_entered_ms = now_ms;
        } else if (btn_b == BTN_SHORT) {
            adjust_setpoint(state, (int16_t)state->prefs.temp_step_c);
            state->screen_entered_ms = now_ms;
        } else if (btn_a == BTN_LONG ||
                   (now_ms - state->screen_entered_ms) >= T90B_SETPOINT_HOLD_MS) {
            ui_enter(state, UI_SCREEN_MAIN_HEAT, now_ms);
        }
        break;

    case UI_SCREEN_MENU:
        if (btn_a == BTN_LONG) {
            /* Cancel edits and return */
            state->menu_editing = false;
            ui_enter(state, UI_SCREEN_STANDBY, now_ms);
        } else if (btn_b == BTN_LONG) {
            if (state->menu_index == 0U) {
                ui_enter(state, UI_SCREEN_STANDBY, now_ms);
            } else if (state->menu_editing) {
                state->prefs = state->edit_prefs;
                prefs_save(&state->prefs);
                state->menu_editing = false;
            } else {
                state->menu_editing = true;
            }
        } else if (btn_a == BTN_SHORT) {
            if (state->menu_editing && state->menu_index == 9U) {
                state->edit_prefs.temp_unit = (state->edit_prefs.temp_unit == TEMP_UNIT_C)
                                                  ? TEMP_UNIT_F
                                                  : TEMP_UNIT_C;
            } else {
                state->menu_index = (uint8_t)((state->menu_index + 15U) % 16U);
            }
        } else if (btn_b == BTN_SHORT) {
            if (state->menu_editing && state->menu_index == 9U) {
                state->edit_prefs.temp_unit = (state->edit_prefs.temp_unit == TEMP_UNIT_C)
                                                  ? TEMP_UNIT_F
                                                  : TEMP_UNIT_C;
            } else {
                state->menu_index = (uint8_t)((state->menu_index + 1U) % 16U);
            }
        }
        break;

    case UI_SCREEN_SLEEP:
        if (any_btn || state->motion_detected) {
            ui_enter(state, UI_SCREEN_MAIN_HEAT, now_ms);
            break;
        }
        stdby_ms = (uint32_t)state->prefs.stdby_time_s * 1000U;
        if (stdby_ms > 0U && (now_ms - state->screen_entered_ms) >= stdby_ms) {
            ui_enter(state, UI_SCREEN_STANDBY, now_ms);
        }
        break;

    case UI_SCREEN_FAULT:
        state->heater_duty_pct = 0U;
        break;

    default:
        ui_enter(state, UI_SCREEN_STANDBY, now_ms);
        break;
    }
}
