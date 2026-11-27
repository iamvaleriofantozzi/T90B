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

#define UI_CAT_COUNT  4U
#define UI_ITEM_COUNT 14U

static const char *const k_cat_names[UI_CAT_COUNT] = {
    "Thermal",
    "Sleep",
    "Power",
    "System"
};

/* Flat table of all 14 settings grouped by category (0..3). */
static const ui_menu_item_t k_menu_items[UI_ITEM_COUNT] = {
    /* 0: Thermal (3 items: flat 0..2) */
    {"Temp Step",  0U, MENU_ITEM_NUM,    1,   25,   1},
    {"Temp Unit",  0U, MENU_ITEM_CYCLE,  0,   1,    1},
    {"Calib",      0U, MENU_ITEM_NUM,   -30,  30,   1},
    /* 1: Sleep (4 items: flat 3..6) */
    {"Wake Heat",  1U, MENU_ITEM_TOGGLE, 0,   1,    1},
    {"Sleep Temp", 1U, MENU_ITEM_NUM,    80,  300,  10},
    {"Sleep Time", 1U, MENU_ITEM_NUM,    0,   600,  30},
    {"Auto Off",   1U, MENU_ITEM_NUM,    0,   900,  60},
    /* 2: Power (3 items: flat 7..9) */
    {"Vin Info",   2U, MENU_ITEM_INFO,   0,   0,    0},
    {"Work Vol",   2U, MENU_ITEM_CYCLE,  0,   3,    1},
    {"Power Trim", 2U, MENU_ITEM_NUM,   -20,  20,   1},
    /* 3: System (4 items: flat 10..13) */
    {"Menu Theme", 3U, MENU_ITEM_CYCLE,  0,   1,    1},
    {"Rotate 180", 3U, MENU_ITEM_TOGGLE, 0,   1,    1},
    {"Restore",    3U, MENU_ITEM_ACTION, 0,   0,    0},
    {"T90B Open",  3U, MENU_ITEM_INFO,   0,   0,    0}
};

static const uint8_t k_cat_offsets[UI_CAT_COUNT] = {0U, 3U, 7U, 10U};
static const uint8_t k_cat_counts[UI_CAT_COUNT]  = {3U, 4U, 3U, 4U};

const char *ui_cat_name(uint8_t cat) {
    return (cat < UI_CAT_COUNT) ? k_cat_names[cat] : "";
}

uint8_t ui_cat_item_count(uint8_t cat) {
    return (cat < UI_CAT_COUNT) ? k_cat_counts[cat] : 0U;
}

uint8_t ui_cat_flat_index(uint8_t cat, uint8_t item_in_cat) {
    if (cat >= UI_CAT_COUNT || item_in_cat >= k_cat_counts[cat]) {
        return 0U;
    }
    return (uint8_t)(k_cat_offsets[cat] + item_in_cat);
}

const ui_menu_item_t *ui_menu_item_info(uint8_t flat_index) {
    if (flat_index >= UI_ITEM_COUNT) {
        return &k_menu_items[0];
    }
    return &k_menu_items[flat_index];
}

const char *ui_menu_label(uint8_t index) {
    if (index >= UI_ITEM_COUNT) {
        return "";
    }
    return k_menu_items[index].label;
}

static void str_copy(char *dst, uint8_t cap, const char *src) {
    uint8_t i = 0U;
    if (cap == 0U) {
        return;
    }
    while (src && src[i] != '\0' && (uint8_t)(i + 1U) < cap) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

static void append_int(char *dst, uint8_t cap, int32_t v, bool signed_plus, const char *suffix) {
    char tmp[12];
    uint8_t n = 0U;
    uint8_t pos = 0U;
    uint32_t mag;

    if (cap == 0U) {
        return;
    }
    if (v < 0) {
        if ((uint8_t)(pos + 1U) < cap) {
            dst[pos++] = '-';
        }
        mag = (uint32_t)(-v);
    } else {
        if (signed_plus && v > 0 && (uint8_t)(pos + 1U) < cap) {
            dst[pos++] = '+';
        }
        mag = (uint32_t)v;
    }
    if (mag == 0U) {
        tmp[n++] = '0';
    } else {
        while (mag > 0U && n < (uint8_t)sizeof(tmp)) {
            tmp[n++] = (char)('0' + (mag % 10U));
            mag /= 10U;
        }
    }
    while (n > 0U && (uint8_t)(pos + 1U) < cap) {
        dst[pos++] = tmp[--n];
    }
    while (suffix && *suffix != '\0' && (uint8_t)(pos + 1U) < cap) {
        dst[pos++] = *suffix++;
    }
    dst[pos] = '\0';
}

void ui_format_item_value(const t90b_state_t *state, uint8_t flat_index, char *buf, uint8_t buf_len) {
    const t90b_prefs_t *p;
    if (!state || !buf || buf_len == 0U) {
        return;
    }
    p = state->menu_editing ? &state->edit_prefs : &state->prefs;
    switch (flat_index) {
    case 0: /* Temp Step */
        append_int(buf, buf_len, (int32_t)p->temp_step_c, false, "C");
        break;
    case 1: /* Temp Unit */
        str_copy(buf, buf_len, (p->temp_unit == TEMP_UNIT_F) ? "F" : "C");
        break;
    case 2: /* Calib */
        append_int(buf, buf_len, (int32_t)p->temp_calib_c, true, "C");
        break;
    case 3: /* Wake Heat */
        str_copy(buf, buf_len, p->power_on_heat ? "ON" : "OFF");
        break;
    case 4: /* Sleep Temp */
        append_int(buf, buf_len, (int32_t)p->sleep_temp_c, false, "C");
        break;
    case 5: /* Sleep Time */
        if (p->sleep_time_s == 0U) {
            str_copy(buf, buf_len, "OFF");
        } else if (p->sleep_time_s < 60U) {
            append_int(buf, buf_len, (int32_t)p->sleep_time_s, false, "s");
        } else {
            append_int(buf, buf_len, (int32_t)(p->sleep_time_s / 60U), false, "m");
        }
        break;
    case 6: /* Auto Off */
        if (p->stdby_time_s == 0U) {
            str_copy(buf, buf_len, "OFF");
        } else if (p->stdby_time_s < 60U) {
            append_int(buf, buf_len, (int32_t)p->stdby_time_s, false, "s");
        } else {
            append_int(buf, buf_len, (int32_t)(p->stdby_time_s / 60U), false, "m");
        }
        break;
    case 7: { /* Vin Info */
        uint16_t dv = (uint16_t)(state->vin_mv / 100U);
        append_int(buf, buf_len, (int32_t)(dv / 10U), false, ".");
        uint8_t pos = 0U;
        while (buf[pos] != '\0') pos++;
        if ((uint8_t)(pos + 2U) < buf_len) {
            buf[pos++] = (char)('0' + (dv % 10U));
            buf[pos++] = 'V';
            buf[pos] = '\0';
        }
        break;
    }
    case 8: /* Work Vol */
        if (p->work_vol_mv == 0U) str_copy(buf, buf_len, "Auto");
        else if (p->work_vol_mv >= 20000U) str_copy(buf, buf_len, "20V");
        else if (p->work_vol_mv >= 12000U) str_copy(buf, buf_len, "12V");
        else str_copy(buf, buf_len, "9V");
        break;
    case 9: /* Power Trim */
        append_int(buf, buf_len, (int32_t)p->power_trim, true, "%");
        break;
    case 10: /* Menu Theme */
        str_copy(buf, buf_len, (p->theme == UI_THEME_STACK) ? "Stack" : "Dock");
        break;
    case 11: /* Rotate 180 */
        str_copy(buf, buf_len, p->rotate_180 ? "ON" : "OFF");
        break;
    case 12: /* Restore */
        str_copy(buf, buf_len, "Hold B");
        break;
    case 13: /* T90B Open */
        str_copy(buf, buf_len, "v2.0");
        break;
    default:
        str_copy(buf, buf_len, "");
        break;
    }
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
    prefs->theme         = UI_THEME_DOCK;
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

static void ui_show_toast(t90b_state_t *state, const char *msg) {
    state->toast_msg = msg;
    state->toast_ticks = 18U; /* ~900 ms at 20 Hz */
}

static void sync_menu_indices(t90b_state_t *state) {
    if (state->prefs.theme == UI_THEME_STACK) {
        if (state->menu_index >= UI_ITEM_COUNT) {
            state->menu_index = 0U;
        }
        state->menu_cat = k_menu_items[state->menu_index].cat;
        state->menu_item = (uint8_t)(state->menu_index - k_cat_offsets[state->menu_cat]);
    } else {
        if (state->menu_cat >= UI_CAT_COUNT) {
            state->menu_cat = 0U;
        }
        if (state->menu_item >= k_cat_counts[state->menu_cat]) {
            state->menu_item = 0U;
        }
        state->menu_index = (uint8_t)(k_cat_offsets[state->menu_cat] + state->menu_item);
    }
}

static void enter_menu(t90b_state_t *state, uint32_t now_ms) {
    state->edit_prefs = state->prefs;
    state->menu_editing = false;
    state->menu_cat = 0U;
    state->menu_item = 0U;
    state->menu_index = 0U;
    state->menu_in_dock = (state->prefs.theme == UI_THEME_DOCK);
    ui_enter(state, UI_SCREEN_MENU, now_ms);
}

static int16_t clamp_i16(int32_t v, int16_t lo, int16_t hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return (int16_t)v;
}

static void adjust_edit_item(t90b_state_t *state, int8_t dir) {
    const uint8_t idx = state->menu_index;
    const ui_menu_item_t *meta = ui_menu_item_info(idx);
    const int32_t delta = (int32_t)dir * (int32_t)meta->step;
    t90b_prefs_t *ep = &state->edit_prefs;

    switch (idx) {
    case 0:
        ep->temp_step_c = (uint8_t)clamp_i16((int32_t)ep->temp_step_c + delta, meta->min_val, meta->max_val);
        break;
    case 2:
        ep->temp_calib_c = clamp_i16((int32_t)ep->temp_calib_c + delta, meta->min_val, meta->max_val);
        break;
    case 4:
        ep->sleep_temp_c = (uint16_t)clamp_i16((int32_t)ep->sleep_temp_c + delta, meta->min_val, meta->max_val);
        break;
    case 5:
        ep->sleep_time_s = (uint16_t)clamp_i16((int32_t)ep->sleep_time_s + delta, meta->min_val, meta->max_val);
        break;
    case 6:
        ep->stdby_time_s = (uint16_t)clamp_i16((int32_t)ep->stdby_time_s + delta, meta->min_val, meta->max_val);
        break;
    case 9:
        ep->power_trim = (int8_t)clamp_i16((int32_t)ep->power_trim + delta, meta->min_val, meta->max_val);
        break;
    default:
        break;
    }
}

static void activate_menu_item(t90b_state_t *state) {
    const uint8_t idx = state->menu_index;
    const ui_menu_item_t *meta = ui_menu_item_info(idx);

    if (meta->type == MENU_ITEM_TOGGLE || meta->type == MENU_ITEM_CYCLE) {
        switch (idx) {
        case 1: /* Temp Unit */
            state->prefs.temp_unit = (state->prefs.temp_unit == TEMP_UNIT_C) ? TEMP_UNIT_F : TEMP_UNIT_C;
            break;
        case 3: /* Wake Heat */
            state->prefs.power_on_heat = state->prefs.power_on_heat ? 0U : 1U;
            break;
        case 8: /* Work Vol */
            if (state->prefs.work_vol_mv == 0U) state->prefs.work_vol_mv = 20000U;
            else if (state->prefs.work_vol_mv >= 20000U) state->prefs.work_vol_mv = 12000U;
            else if (state->prefs.work_vol_mv >= 12000U) state->prefs.work_vol_mv = 9000U;
            else state->prefs.work_vol_mv = 0U;
            break;
        case 10: /* Menu Theme (Dock <-> Stack) */
            state->prefs.theme = (state->prefs.theme == UI_THEME_DOCK) ? UI_THEME_STACK : UI_THEME_DOCK;
            state->menu_in_dock = false;
            sync_menu_indices(state);
            ui_show_toast(state, (state->prefs.theme == UI_THEME_STACK) ? "Stack" : "Dock");
            break;
        case 11: /* Rotate 180 */
            state->prefs.rotate_180 = state->prefs.rotate_180 ? 0U : 1U;
            break;
        default:
            break;
        }
        state->edit_prefs = state->prefs;
        prefs_save(&state->prefs);
    } else if (meta->type == MENU_ITEM_NUM) {
        state->edit_prefs = state->prefs;
        state->menu_editing = true;
    } else if (meta->type == MENU_ITEM_ACTION && idx == 12U) {
        prefs_load_defaults(&state->prefs);
        state->edit_prefs = state->prefs;
        prefs_save(&state->prefs);
        state->menu_in_dock = (state->prefs.theme == UI_THEME_DOCK);
        sync_menu_indices(state);
        ui_show_toast(state, "Restored");
    }
}

void ui_init(t90b_state_t *state, uint8_t factory_flag, const t90b_prefs_t *initial_prefs) {
    if (!state) {
        return;
    }
    state->now_ms = 0U;
    state->screen_entered_ms = 0U;
    state->last_activity_ms = 0U;
    state->menu_index = 0U;
    state->menu_cat = 0U;
    state->menu_item = 0U;
    state->menu_editing = false;
    state->factory_flag = factory_flag;
    state->faults = FAULT_NONE;
    state->tip_temp_dc = 250;
    state->vin_mv = 20000U;
    state->motion_detected = false;
    state->heater_duty_pct = 0U;
    state->toast_ticks = 0U;
    state->toast_msg = "";

    if (initial_prefs) {
        state->prefs = *initial_prefs;
    } else {
        prefs_load_defaults(&state->prefs);
    }
    state->edit_prefs = state->prefs;
    state->menu_in_dock = (state->prefs.theme == UI_THEME_DOCK);
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
    if (state->toast_ticks > 0U) {
        state->toast_ticks--;
    }
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
            enter_menu(state, now_ms);
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
            enter_menu(state, now_ms);
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
        if (btn_a == BTN_SHORT && btn_b == BTN_SHORT) {
            state->menu_editing = false;
            ui_enter(state, UI_SCREEN_STANDBY, now_ms);
            break;
        }
        if (btn_a == BTN_LONG) {
            if (state->menu_editing) {
                state->edit_prefs = state->prefs;
                state->menu_editing = false;
                ui_show_toast(state, "Cancel");
            } else if (state->prefs.theme == UI_THEME_DOCK && !state->menu_in_dock) {
                state->menu_in_dock = true;
            } else {
                ui_enter(state, UI_SCREEN_STANDBY, now_ms);
            }
            break;
        }
        if (btn_b == BTN_LONG) {
            if (state->prefs.theme == UI_THEME_DOCK && state->menu_in_dock) {
                state->menu_in_dock = false;
                state->menu_item = 0U;
                sync_menu_indices(state);
            } else if (state->menu_editing) {
                state->prefs = state->edit_prefs;
                prefs_save(&state->prefs);
                state->menu_editing = false;
                ui_show_toast(state, "Saved");
            } else {
                activate_menu_item(state);
            }
            break;
        }
        if (btn_a == BTN_SHORT || btn_b == BTN_SHORT) {
            const int8_t dir = (btn_b == BTN_SHORT) ? 1 : -1;
            if (state->menu_editing) {
                adjust_edit_item(state, dir);
            } else if (state->prefs.theme == UI_THEME_DOCK && state->menu_in_dock) {
                state->menu_cat = (uint8_t)((state->menu_cat + UI_CAT_COUNT + dir) % UI_CAT_COUNT);
                state->menu_item = 0U;
                sync_menu_indices(state);
            } else if (state->prefs.theme == UI_THEME_DOCK) {
                const uint8_t cnt = k_cat_counts[state->menu_cat];
                state->menu_item = (uint8_t)((state->menu_item + cnt + dir) % cnt);
                sync_menu_indices(state);
            } else {
                state->menu_index = (uint8_t)((state->menu_index + UI_ITEM_COUNT + dir) % UI_ITEM_COUNT);
                sync_menu_indices(state);
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
