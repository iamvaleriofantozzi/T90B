#include "t90b.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* Host stub for board_set_heater_pwm */
#define EXPECTED_PWM(request) (T90B_HEATER_ENABLED ? (request) : 0U)

static uint8_t g_last_pwm = 255U;
void board_set_heater_pwm(uint8_t duty_pct) {
    g_last_pwm = duty_pct;
}

static void test_boot_and_factory_gate(void) {
    t90b_state_t s;
    t90b_prefs_t p;
    prefs_load_defaults(&p);

    ui_init(&s, 0x00U, &p);
    assert(s.screen == UI_SCREEN_FACTORY);

    ui_step(&s, 50U, BTN_SHORT, BTN_SHORT);
    assert(s.factory_flag == T90B_PREFS_MAGIC_OK);
    assert(s.screen == UI_SCREEN_BOOT_LOGO);

    ui_step(&s, T90B_BOOT_LOGO_MS + 50U, BTN_NONE, BTN_NONE);
    assert(s.screen == UI_SCREEN_STANDBY);
    assert(s.heater_duty_pct == 0U);
}

static void test_menu_and_settings_persistence(void) {
    t90b_state_t s;
    t90b_prefs_t p;
    prefs_load_defaults(&p);
    ui_init(&s, T90B_PREFS_MAGIC_OK, &p);
    ui_step(&s, 1300U, BTN_NONE, BTN_NONE);
    assert(s.screen == UI_SCREEN_STANDBY);

    /* Enter menu with A+B -> starts in Dock mode (Thermal) */
    ui_step(&s, 1350U, BTN_SHORT, BTN_SHORT);
    assert(s.screen == UI_SCREEN_MENU);
    assert(s.menu_in_dock);
    assert(s.menu_cat == 0U);

    /* Open Thermal list with B long, move to item 1 (Temp Unit) */
    ui_step(&s, 1400U, BTN_NONE, BTN_LONG);
    assert(!s.menu_in_dock);
    ui_step(&s, 1450U, BTN_NONE, BTN_SHORT);
    assert(s.menu_index == 1U);
    assert(strcmp(ui_menu_label(1U), "Temp Unit") == 0);

    /* Toggle Temp Unit directly with B long -> saves F */
    ui_step(&s, 1500U, BTN_NONE, BTN_LONG);
    assert(s.prefs.temp_unit == TEMP_UNIT_F);

    /* Return to Dock with A long, navigate to System (cat 3) */
    ui_step(&s, 1550U, BTN_LONG, BTN_NONE);
    assert(s.menu_in_dock);
    ui_step(&s, 1600U, BTN_SHORT, BTN_NONE); /* wrap 0 -> 3 (System) */
    assert(s.menu_cat == 3U);

    /* Enter System -> item 0 is Menu Theme; B long switches Dock -> Stack */
    ui_step(&s, 1650U, BTN_NONE, BTN_LONG);
    assert(s.menu_index == 10U);
    assert(strcmp(ui_menu_label(10U), "Menu Theme") == 0);
    ui_step(&s, 1700U, BTN_NONE, BTN_LONG);
    assert(s.prefs.theme == UI_THEME_STACK);

    /* Navigate to Temp Step (item 0), edit and cancel with A long */
    ui_step(&s, 1750U, BTN_NONE, BTN_SHORT); /* 11 */
    ui_step(&s, 1800U, BTN_NONE, BTN_SHORT); /* 12 */
    ui_step(&s, 1850U, BTN_NONE, BTN_SHORT); /* 13 */
    ui_step(&s, 1900U, BTN_NONE, BTN_SHORT); /* 0: Temp Step */
    assert(s.menu_index == 0U);
    ui_step(&s, 1950U, BTN_NONE, BTN_LONG);
    assert(s.menu_editing);
    ui_step(&s, 2000U, BTN_NONE, BTN_SHORT);
    assert(s.edit_prefs.temp_step_c == 6U);
    ui_step(&s, 2050U, BTN_LONG, BTN_NONE);
    assert(!s.menu_editing);
    assert(s.prefs.temp_step_c == 5U);

    /* Exit menu with A+B */
    ui_step(&s, 2100U, BTN_SHORT, BTN_SHORT);
    assert(s.screen == UI_SCREEN_STANDBY);
}

static void test_setpoint_sleep_wake_and_faults(void) {
    t90b_state_t s;
    t90b_prefs_t p;
    prefs_load_defaults(&p);
    ui_init(&s, T90B_PREFS_MAGIC_OK, &p);
    ui_step(&s, 1300U, BTN_NONE, BTN_NONE);

    /* Start heating with A short */
    ui_step(&s, 1350U, BTN_SHORT, BTN_NONE);
    assert(s.screen == UI_SCREEN_MAIN_HEAT);

    /* Adjust setpoint */
    ui_step(&s, 1400U, BTN_NONE, BTN_SHORT);
    assert(s.screen == UI_SCREEN_SETPOINT);
    ui_step(&s, 1450U, BTN_NONE, BTN_SHORT);
    assert(s.prefs.setpoint_c == 355U);

    /* Hold timeout returns to MAIN_HEAT */
    ui_step(&s, 1450U + T90B_SETPOINT_HOLD_MS, BTN_NONE, BTN_NONE);
    assert(s.screen == UI_SCREEN_MAIN_HEAT);

    /* Sleep after 180s inactivity */
    ui_step(&s, 1450U + T90B_SETPOINT_HOLD_MS + T90B_SLEEP_TIMEOUT_MS, BTN_NONE, BTN_NONE);
    assert(s.screen == UI_SCREEN_SLEEP);

    /* Wake on motion */
    s.motion_detected = true;
    ui_step(&s, 200000U, BTN_NONE, BTN_NONE);
    s.motion_detected = false;
    assert(s.screen == UI_SCREEN_MAIN_HEAT);

    /* Fault forces FAULT screen and 0% heater */
    s.faults = FAULT_TIP_MISSING;
    ui_step(&s, 200050U, BTN_NONE, BTN_NONE);
    assert(s.screen == UI_SCREEN_FAULT);
    assert(s.heater_duty_pct == 0U);
}

static void test_heater_safe_state(void) {
    heater_ctrl_t h;
    heater_init(&h);
    assert(!h.armed);
    assert(g_last_pwm == 0U);

    assert(!heater_rearm(&h, FAULT_TIP_MISSING, true, 100U));
    assert(heater_rearm(&h, FAULT_NONE, true, 100U));
    assert(heater_step(&h, true, 350, 250, FAULT_NONE, 150U) == 20U);
    assert(g_last_pwm == EXPECTED_PWM(20U));
    assert(heater_step(&h, true, 350, 3450, FAULT_NONE, 160U) == 10U);
    assert(g_last_pwm == EXPECTED_PWM(10U));
    assert(heater_step(&h, true, 350, 3500, FAULT_NONE, 170U) == 0U);
    assert(g_last_pwm == 0U);
    assert(heater_step(&h, true, 350, 3550, FAULT_NONE, 180U) == 0U);
    assert(heater_step(&h, true, 350, 250, FAULT_NONE, 190U) == 20U);
    assert(g_last_pwm == EXPECTED_PWM(20U));
    assert(heater_step(&h, true, 350, 250, FAULT_SENSOR, 200U) == 0U);
    assert(h.tripped);
    assert(!h.armed);
}

static void test_heater_sample_freshness(void) {
    heater_ctrl_t h;
    heater_init(&h);
    assert(heater_rearm(&h, FAULT_NONE, true, 100U));
    heater_record_sample(&h, FAULT_NONE, 600U);
    assert(h.armed && h.last_sensor_ms == 600U);
    heater_record_sample(&h, FAULT_NONE, 1101U);
    assert(h.tripped && h.trip_reason == FAULT_SENSOR && g_last_pwm == 0U);
    heater_record_sample(&h, FAULT_NONE, 1150U);
    assert(h.tripped && !h.armed);

    const uint32_t faults[] = {FAULT_TIP_MISSING, FAULT_NTC, FAULT_VOL_LOW, FAULT_SENSOR};
    for (unsigned i = 0; i < sizeof(faults) / sizeof(faults[0]); i++) {
        assert(heater_rearm(&h, FAULT_NONE, true, 1200U));
        heater_record_sample(&h, faults[i], 1250U);
        assert(h.tripped && h.trip_reason == faults[i] && g_last_pwm == 0U);
    }
}

static void test_normal_heater_command(void) {
    heater_ctrl_t h;
    t90b_state_t s;
    t90b_prefs_t prefs;
    prefs_load_defaults(&prefs);
    prefs.power_on_heat = 1U;
    ui_init(&s, T90B_PREFS_MAGIC_OK, &prefs);
    heater_init(&h);
    uint32_t now = T90B_BOOT_LOGO_MS + 1U;
    heater_ui_step(&h, &s, now++, BTN_SHORT, BTN_NONE);
    assert(!h.armed && s.screen == UI_SCREEN_STANDBY);

    s.faults = FAULT_VOL_LOW;
    heater_ui_step(&h, &s, now++, BTN_SHORT, BTN_NONE);
    assert(!h.armed && s.screen == UI_SCREEN_FAULT);
    s.faults = FAULT_NONE;
    heater_ui_step(&h, &s, now++, BTN_SHORT, BTN_NONE);
    assert(!h.armed && s.screen == UI_SCREEN_STANDBY);
    heater_ui_step(&h, &s, now++, BTN_SHORT, BTN_NONE);
    assert(h.armed && s.screen == UI_SCREEN_MAIN_HEAT && g_last_pwm == EXPECTED_PWM(20U));

    now += 600U;
    heater_ui_step(&h, &s, now++, BTN_NONE, BTN_NONE);
    assert(!h.armed && h.trip_reason == FAULT_SENSOR && s.screen == UI_SCREEN_FAULT);
    assert(g_last_pwm == 0U);
    s.faults = FAULT_NONE;
    heater_ui_step(&h, &s, now++, BTN_NONE, BTN_NONE);
    assert(!h.armed && s.screen == UI_SCREEN_STANDBY);
    heater_ui_step(&h, &s, now++, BTN_SHORT, BTN_NONE);
    assert(h.armed && !h.tripped && g_last_pwm == EXPECTED_PWM(20U));
    s.faults = FAULT_TIP_MISSING;
    heater_ui_step(&h, &s, now++, BTN_NONE, BTN_NONE);
    assert(!h.armed && s.screen == UI_SCREEN_FAULT && g_last_pwm == 0U);
    s.faults = FAULT_NONE;
    heater_ui_step(&h, &s, now++, BTN_NONE, BTN_NONE);
    assert(!h.armed && s.screen == UI_SCREEN_STANDBY && g_last_pwm == 0U);
    heater_ui_step(&h, &s, now++, BTN_SHORT, BTN_NONE);
    assert(h.armed && g_last_pwm == EXPECTED_PWM(20U));
    heater_ui_step(&h, &s, now++, BTN_LONG, BTN_NONE);
    assert(!h.armed && s.screen == UI_SCREEN_STANDBY && g_last_pwm == 0U);
}

int main(void) {
    test_boot_and_factory_gate();
    test_menu_and_settings_persistence();
    test_setpoint_sleep_wake_and_faults();
    test_heater_safe_state();
    test_heater_sample_freshness();
    test_normal_heater_command();
    printf("All T90B host UI & safety tests passed.\n");
    return 0;
}
