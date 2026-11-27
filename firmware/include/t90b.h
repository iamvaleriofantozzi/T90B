#ifndef T90B_H
#define T90B_H

#include <stdbool.h>
#include <stdint.h>

/* Heater output enable gate: MUST remain 0 until T3.2 bench gates pass. */
#ifndef T90B_HEATER_ENABLED
#define T90B_HEATER_ENABLED 0
#endif

#ifndef T90B_HEAT_PROBE
#define T90B_HEAT_PROBE 0
#endif

#define T90B_SENSOR_TIMEOUT_MS 500U
#ifndef T90B_HEAT_TOGGLE_TEST
#define T90B_HEAT_TOGGLE_TEST 0
#endif
#if T90B_HEAT_TOGGLE_TEST
#define T90B_HEAT_PROBE_MAX_DUTY 100U
#else
#define T90B_HEAT_PROBE_DURATION_MS 1000U
#define T90B_HEAT_PROBE_MAX_DUTY 10U
#endif

#define T90B_APP_BASE          0x08005000UL
#define T90B_PREFS_PAGE        0x0801F000UL
#define T90B_PREFS_MAGIC_OK    0xAAU

#define T90B_TEMP_MIN_C        100
#define T90B_TEMP_MAX_C        450
#define T90B_TEMP_DEFAULT_C    350
#define T90B_SLEEP_TEMP_C      150

#if T90B_HEAT_PRESETS
#define T90B_PRESET_MAX_C 400
/* Returns zero for an unsupported target. */
uint16_t next_heat_preset(uint16_t current_c);
#endif

#define T90B_BOOT_LOGO_MS      1250U
#define T90B_SETPOINT_HOLD_MS  3000U
#define T90B_SLEEP_TIMEOUT_MS  180000U
#define T90B_STDBY_TIMEOUT_MS  180000U

typedef enum {
    UI_SCREEN_BOOT_LOGO = 0,
    UI_SCREEN_STANDBY   = 1,
    UI_SCREEN_MAIN_HEAT = 2,
    UI_SCREEN_MENU      = 3,
    UI_SCREEN_SETPOINT  = 4,
    UI_SCREEN_SLEEP     = 5,
    UI_SCREEN_FAULT     = 9,
    UI_SCREEN_FACTORY   = 12
} ui_screen_t;

typedef enum {
    BTN_NONE  = 0,
    BTN_SHORT = 1,
    BTN_LONG  = 2
} btn_event_t;

typedef enum {
    FAULT_NONE       = 0x00U,
    FAULT_TIP_MISSING = 0x01U,
    FAULT_SENSOR     = 0x02U,
    FAULT_NTC        = 0x04U,
    FAULT_VOL_LOW    = 0x08U,
    FAULT_THERMAL    = 0x10U
} fault_mask_t;

typedef enum {
    TEMP_UNIT_C = 0,
    TEMP_UNIT_F = 1
} temp_unit_t;

typedef enum {
    UI_THEME_DOCK  = 0, /* Theme A: Watch Minimal + Dynamic 4-category Dock */
    UI_THEME_STACK = 1  /* Theme B: Pro Telemetry + WatchOS Smart Stack */
} ui_theme_t;

typedef struct {
    uint16_t setpoint_c;
    uint16_t sleep_temp_c;
    uint8_t  temp_step_c;
    uint8_t  temp_unit;
    uint8_t  language;
    uint8_t  rotate_180;
    uint8_t  power_on_heat;
    uint8_t  theme;
    uint16_t sleep_time_s;
    uint16_t stdby_time_s;
    uint16_t work_vol_mv;
    int8_t   power_trim;
    int16_t  temp_calib_c;
} t90b_prefs_t;

typedef struct {
    ui_screen_t  screen;
    uint32_t     now_ms;
    uint32_t     screen_entered_ms;
    uint32_t     last_activity_ms;
    uint8_t      menu_index;
    uint8_t      menu_cat;
    uint8_t      menu_item;
    bool         menu_in_dock;
    bool         menu_editing;
    uint8_t      factory_flag;
    uint32_t     faults;
    int16_t      tip_temp_dc; /* Tenths of a degree Celsius. */
    uint16_t     vin_mv;
    bool         motion_detected;
    t90b_prefs_t prefs;
    t90b_prefs_t edit_prefs;
    uint8_t      heater_duty_pct;
    uint8_t      toast_ticks;
    const char  *toast_msg;
#if T90B_HEAT_PRESETS
    uint16_t     preset_c;
#endif
} t90b_state_t;

/* Board & hardware abstraction (board.c) */
void board_init(void);
void board_set_heater_pwm(uint8_t duty_pct);
void board_watchdog_reload(void);
void board_delay_ms(uint32_t ms);
uint32_t board_millis(void);
void board_poll_inputs(btn_event_t *btn_a, btn_event_t *btn_b, uint32_t *faults,
                       int16_t *tip_temp_dc, uint16_t *vin_mv, bool *motion);
#if T90B_FAULT_TEST
void board_render_fault_test(uint32_t faults, uint32_t trip_reason, bool armed);
#endif
void board_render_ui(const t90b_state_t *state);

/* Preferences helpers (ui.c) */
void prefs_load_defaults(t90b_prefs_t *prefs);
bool prefs_validate_block(const uint8_t *buf, uint32_t len);
uint32_t prefs_checksum_u8(const uint8_t *buf, uint32_t len);
bool prefs_save(const t90b_prefs_t *prefs);

/* UI state machine (ui.c) */
typedef enum {
    MENU_ITEM_TOGGLE = 0,
    MENU_ITEM_CYCLE  = 1,
    MENU_ITEM_NUM    = 2,
    MENU_ITEM_INFO   = 3,
    MENU_ITEM_ACTION = 4
} menu_item_type_t;

typedef struct {
    const char      *label;
    uint8_t          cat;
    menu_item_type_t type;
    int16_t          min_val;
    int16_t          max_val;
    int16_t          step;
} ui_menu_item_t;

void ui_init(t90b_state_t *state, uint8_t factory_flag, const t90b_prefs_t *initial_prefs);
void ui_step(t90b_state_t *state, uint32_t now_ms, btn_event_t btn_a, btn_event_t btn_b);
const char *ui_menu_label(uint8_t index);
const char *ui_cat_name(uint8_t cat);
uint8_t ui_cat_item_count(uint8_t cat);
uint8_t ui_cat_flat_index(uint8_t cat, uint8_t item_in_cat);
const ui_menu_item_t *ui_menu_item_info(uint8_t flat_index);
void ui_format_item_value(const t90b_state_t *state, uint8_t flat_index, char *buf, uint8_t buf_len);

/* Heater safety controller (heater.c) */
typedef struct {
    bool     armed;
    bool     tripped;
    uint32_t last_sensor_ms;
#if T90B_HEAT_PROBE && !T90B_HEAT_TOGGLE_TEST
    uint32_t armed_since_ms;
#endif
    uint32_t trip_reason;
    uint8_t  duty_pct;
#if T90B_HEAT_TOGGLE_TEST
#if T90B_HEAT_PRESETS
    int16_t cooldown_low_dc; /* Lowest residual temperature since a hot start. */
#endif
    bool checking_rise;
    int16_t rise_start_dc;
    uint32_t rise_start_ms;
    bool pid_started;
    uint32_t pid_sample_ms;
    int16_t pid_previous_dc;
    int32_t pid_integral;
    int32_t pid_derivative;
#endif
} heater_ctrl_t;

void heater_init(heater_ctrl_t *ctrl);
void heater_trip(heater_ctrl_t *ctrl, uint32_t reason);
bool heater_rearm(heater_ctrl_t *ctrl, uint32_t faults, bool sensor_valid, uint32_t now_ms);
void heater_record_sample(heater_ctrl_t *ctrl, uint32_t faults, uint32_t now_ms);
void heater_ui_step(heater_ctrl_t *ctrl, t90b_state_t *ui, uint32_t now_ms,
                    btn_event_t btn_a, btn_event_t btn_b);
uint8_t heater_step(heater_ctrl_t *ctrl, bool heat_requested, int16_t target_c,
                    int16_t actual_dc, uint32_t faults, uint32_t now_ms);

#endif /* T90B_H */
