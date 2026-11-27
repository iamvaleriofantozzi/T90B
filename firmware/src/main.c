#include "t90b.h"

#if T90B_FAULT_TEST
_Static_assert(!T90B_HEATER_ENABLED, "Fault test requires heater disabled");
#endif

int main(void) {
    t90b_state_t ui;
    heater_ctrl_t heater;
    t90b_prefs_t prefs;
    const uint8_t *flash_prefs = (const uint8_t *)T90B_PREFS_PAGE;
    uint8_t factory_flag = 0U;

    board_init();
    heater_init(&heater);

    prefs_load_defaults(&prefs);
    if (prefs_validate_block(flash_prefs + 0x14U, 0x1CU)) {
        factory_flag = flash_prefs[0x14U + 5U];
    }

    ui_init(&ui, factory_flag, &prefs);

    for (;;) {
        btn_event_t btn_a = BTN_NONE;
        btn_event_t btn_b = BTN_NONE;
        uint32_t faults = FAULT_NONE;
        int16_t tip_temp_dc = 250;
        uint16_t vin_mv = 20000U;
        bool motion = false;

        board_poll_inputs(&btn_a, &btn_b, &faults, &tip_temp_dc, &vin_mv, &motion);
        uint32_t now_ms = board_millis();
#if T90B_FAULT_TEST
        if (btn_a == BTN_SHORT && btn_b == BTN_NONE) {
            heater_rearm(&heater, faults, faults == FAULT_NONE, now_ms);
        }
        if (btn_b == BTN_SHORT && btn_a == BTN_NONE && heater.armed) {
            /* Simulate a 600 ms sampling gap while presenting a new ADC sample. */
            heater.last_sensor_ms = now_ms - 600U;
        }
        heater_record_sample(&heater, faults, now_ms);
        board_render_fault_test(faults, heater.trip_reason, heater.armed);
#else
        ui.faults = faults;
        ui.tip_temp_dc = tip_temp_dc;
        ui.vin_mv = vin_mv;
        ui.motion_detected = motion;
        heater_ui_step(&heater, &ui, now_ms, btn_a, btn_b);
        board_render_ui(&ui);
#endif
        board_watchdog_reload();
        board_delay_ms(50U);
    }
}
