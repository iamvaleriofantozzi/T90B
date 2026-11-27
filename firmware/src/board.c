#include "t90b.h"

#define T90B_MINIMAL_BOOT_TEST 0

#ifndef T90B_LCD_TEST
#define T90B_LCD_TEST 0
#endif

#ifndef T90B_ADC_TEST
#define T90B_ADC_TEST 0
#endif

#ifndef T90B_TEMP_TEST
#define T90B_TEMP_TEST 0
#endif

#ifndef T90B_HEATER_OFF_TEST
#define T90B_HEATER_OFF_TEST 0
#endif

_Static_assert(!T90B_HEATER_OFF_TEST || !T90B_HEATER_ENABLED,
               "Off-state test must not allow power");
_Static_assert(!(T90B_LCD_TEST || T90B_ADC_TEST || T90B_TEMP_TEST) || !T90B_HEATER_ENABLED,
               "Diagnostic builds require the heater to be disabled");

#if !T90B_MINIMAL_BOOT_TEST
static unsigned tip_group;
static int tip_temperature_dc(uint16_t raw, int ambient_dc);
static int16_t ntc_temperature_dc(uint16_t sample);
#endif
#if T90B_TEMP_TEST
static uint16_t cold_ntc_adc, cold_tip_adc;
#endif

#if T90B_ADC_TEST
static uint16_t adc_samples[7], adc_injected_samples[7];
#endif

/* NVIC interrupt clear registers */
#define NVIC_ICER0     (*(volatile uint32_t *)0xE000E180UL)
#define NVIC_ICER1     (*(volatile uint32_t *)0xE000E184UL)
#define NVIC_ICER2     (*(volatile uint32_t *)0xE000E188UL)
#define NVIC_ICPR0     (*(volatile uint32_t *)0xE000E280UL)
#define NVIC_ICPR1     (*(volatile uint32_t *)0xE000E284UL)
#define NVIC_ICPR2     (*(volatile uint32_t *)0xE000E288UL)

/* Core & Cortex-M4 registers */
#define SCB_VTOR       (*(volatile uint32_t *)0xE000ED08UL)
#define SYST_CSR       (*(volatile uint32_t *)0xE000E010UL)
#define SYST_RVR       (*(volatile uint32_t *)0xE000E014UL)
#define SYST_CVR       (*(volatile uint32_t *)0xE000E018UL)

/* RCC registers (N32L403) */
#define RCC_CTRL       (*(volatile uint32_t *)0x40021000UL)
#define RCC_CFG2       (*(volatile uint32_t *)0x4002102CUL)
#define RCC_CFG        (*(volatile uint32_t *)0x40021004UL)
#define RCC_AHBPCLKEN  (*(volatile uint32_t *)0x40021014UL)
#define RCC_APB2PCLKEN (*(volatile uint32_t *)0x40021018UL)
#define RCC_APB1PCLKEN (*(volatile uint32_t *)0x4002101CUL)

/* GPIO bases (N32L403: PMODE +0x00, POTYPE +0x04, SR +0x08, PUPD +0x0C,
 * PID +0x10, POD +0x14, PBSC +0x18, PLOCK +0x1C, AFL +0x20, AFH +0x24, PBC +0x28, DS +0x2C) */
#define GPIOA_BASE     0x40010800UL
#define GPIOB_BASE     0x40010C00UL
#define GPIOD_BASE     0x40011400UL
#define GPIO_REG(base, off) (*(volatile uint32_t *)((base) + (off)))
#define GPIO_PBSC_OFF  0x18U
#define GPIO_PBC_OFF   0x28U

/* SPI1 registers */
#define SPI1_CTRL1     (*(volatile uint32_t *)0x40013000UL)
#define SPI1_CTRL2     (*(volatile uint32_t *)0x40013004UL)
#define SPI1_STS       (*(volatile uint32_t *)0x40013008UL)
#define SPI1_DAT       (*(volatile uint16_t *)0x4001300CUL)
#define SPI1_I2SCFGR   (*(volatile uint32_t *)0x4001301CUL)
#define SPI1_ENABLE    (1UL << 6)
#define SPI1_FRAME_16  (1UL << 11)

/* ADC1 registers (N32L403) */
#define ADC1_STS       (*(volatile uint32_t *)0x40020800UL)
#define ADC1_CTRL1     (*(volatile uint32_t *)0x40020804UL)
#define ADC1_CTRL2     (*(volatile uint32_t *)0x40020808UL)
#define ADC1_SMPR2     (*(volatile uint32_t *)0x40020810UL)
#define ADC1_RSEQ1     (*(volatile uint32_t *)0x4002082CUL)
#define ADC1_JSEQ      (*(volatile uint32_t *)0x40020838UL)
#define ADC1_JDAT1     (*(volatile uint32_t *)0x4002083CUL)
#define ADC1_RSEQ3     (*(volatile uint32_t *)0x40020834UL)
#define ADC1_DAT       (*(volatile uint32_t *)0x4002084CUL)
#define ADC1_CALFACT   (*(volatile uint32_t *)0x40020854UL)
#define ADC1_CTRL3     (*(volatile uint32_t *)0x40020858UL)
#define ADC1_ON        (1UL << 0)
#define ADC1_CALIBRATE (1UL << 2)
#define ADC1_READY     (1UL << 5)
#define ADC1_SW_RSEL   (7UL << 17)
#define ADC1_RTRIG     (1UL << 20)
#define ADC1_SW_START  (1UL << 22)
#define ADC1_VREF_ON   (1UL << 23)
#define ADC1_SW_JSEL   (7UL << 12)
#define ADC1_JTRIG     (1UL << 15)

/* Original heater output is PA0 AF2, timer at 0x40000000. */
#define HEAT_TIM_CTRL1  (*(volatile uint32_t *)0x40000000UL)
#define HEAT_TIM_EVT    (*(volatile uint32_t *)0x40000014UL)
#define HEAT_TIM_MODE   (*(volatile uint32_t *)0x40000018UL)
#define HEAT_TIM_CCEN   (*(volatile uint32_t *)0x40000020UL)
#define HEAT_TIM_PSC    (*(volatile uint32_t *)0x40000028UL)
#define HEAT_TIM_ARR    (*(volatile uint32_t *)0x4000002CUL)
#define HEAT_TIM_CCR    (*(volatile uint32_t *)0x40000034UL)
#define HEAT_FORCE_LOW  0x40U
#define HEAT_PWM_MODE   0x60U
/* 16 MHz timer clock, approximately 60 kHz as in the original. */
#define HEAT_PERIOD_TICKS 267U
#define HEAT_CARRIER_HIGH_TICKS ((HEAT_PERIOD_TICKS * 90U) / 100U)
#define HEAT_WINDOW_MS 100U
#define HEAT_ADC_SETTLE_TICKS 2U


/* IWDG registers */
#define IWDG_KEY       (*(volatile uint32_t *)0x40003000UL)
#define IWDG_PREDIV    (*(volatile uint32_t *)0x40003004UL)
#define IWDG_RELV      (*(volatile uint32_t *)0x40003008UL)

/* Pin assignments extracted from t90-app.bin & bootloader */
#define PIN_LCD_BL     (1UL << 6)   /* PA6, active LOW */
#define PIN_LCD_CS     (1UL << 10)  /* PA10, active LOW */
#define PIN_LCD_DC     (1UL << 0)   /* PD0, LOW=cmd, HIGH=data */
#define PIN_BTN_A      (1UL << 15)  /* PA15, active LOW */
#define PIN_BTN_B      (1UL << 4)   /* PB4, active LOW */

#define LCD_W 160U
#define LCD_H 40U

static volatile uint32_t g_tick_ms = 0U;
static uint8_t g_hold_btn = 0U; /* 0=none, 1=A, 2=B */
static uint8_t g_hold_pct = 0U; /* 0..100 */

#if T90B_HEATER_ENABLED
static volatile uint32_t pwm_last_update_ms;
#if T90B_HEAT_PROBE && !T90B_HEAT_TOGGLE_TEST
static volatile uint32_t pwm_pulse_start_ms;
#endif
static volatile bool pwm_timeout_latched;
static volatile bool pwm_adc_paused;
static volatile uint8_t pwm_request_pct;
static uint8_t pwm_phase_ms;
#endif

void SysTick_Handler(void) {
    g_tick_ms++;
#if T90B_HEATER_ENABLED
    bool timed_out = g_tick_ms - pwm_last_update_ms > T90B_SENSOR_TIMEOUT_MS;
#if T90B_HEAT_PROBE && !T90B_HEAT_TOGGLE_TEST
    timed_out |= g_tick_ms - pwm_pulse_start_ms >= T90B_HEAT_PROBE_DURATION_MS;
#endif
    if (pwm_request_pct != 0U && timed_out) {
        HEAT_TIM_MODE = HEAT_FORCE_LOW;
        pwm_request_pct = 0U;
        pwm_timeout_latched = true;
    }
    if (pwm_request_pct != 0U && !pwm_adc_paused) {
        HEAT_TIM_MODE = pwm_phase_ms < pwm_request_pct ? HEAT_PWM_MODE : HEAT_FORCE_LOW;
        if (++pwm_phase_ms == HEAT_WINDOW_MS) {
            pwm_phase_ms = 0U;
        }
    }
#endif
}

static void gpio_config_pin(uint32_t base, uint8_t pin, uint32_t mode,
                            uint32_t pupd, uint32_t af) {
    uint32_t shift2 = (uint32_t)pin * 2U;
    uint32_t pmode = GPIO_REG(base, 0x00U);
    uint32_t ppupd = GPIO_REG(base, 0x0CU);

    if (mode == 2U || mode == 0U) {
        uint32_t af_off = (pin < 8U) ? 0x20U : 0x24U;
        uint32_t shift4 = (uint32_t)(pin & 7U) * 4U;
        uint32_t af_reg = GPIO_REG(base, af_off);
        af_reg = (af_reg & ~(0xFUL << shift4)) | ((af & 0xFUL) << shift4);
        GPIO_REG(base, af_off) = af_reg;
    }

    pmode = (pmode & ~(3UL << shift2)) | ((mode & 3UL) << shift2);
    ppupd = (ppupd & ~(3UL << shift2)) | ((pupd & 3UL) << shift2);
    GPIO_REG(base, 0x00U) = pmode;
    GPIO_REG(base, 0x0CU) = ppupd;

    if (mode == 1U || mode == 2U) {
        GPIO_REG(base, 0x04U) &= ~(1UL << pin); /* Push-pull */
        GPIO_REG(base, 0x08U) &= ~(1UL << pin); /* Fast slew rate */
    }
}

#if !T90B_MINIMAL_BOOT_TEST
static void spi1_write_frame(uint16_t frame) {
    uint32_t guard = 2000U;
    while (((SPI1_STS & (1UL << 1)) == 0U) && (guard-- > 0U)) {
    }
    SPI1_DAT = frame;
    guard = 2000U;
    while (((SPI1_STS & (1UL << 1)) == 0U) && (guard-- > 0U)) {
    }
    guard = 2000U;
    while (((SPI1_STS & (1UL << 7)) != 0U) && (guard-- > 0U)) {
    }
}

static void lcd_cmd(uint8_t cmd) {
    GPIO_REG(GPIOD_BASE, GPIO_PBC_OFF)  = PIN_LCD_DC;  /* DC = 0 */
    GPIO_REG(GPIOA_BASE, GPIO_PBC_OFF)  = PIN_LCD_CS;  /* CS = 0 */
    spi1_write_frame(cmd);
    GPIO_REG(GPIOA_BASE, GPIO_PBSC_OFF) = PIN_LCD_CS;  /* CS = 1 */
}

static void lcd_data(uint8_t dat) {
    GPIO_REG(GPIOD_BASE, GPIO_PBSC_OFF) = PIN_LCD_DC;  /* DC = 1 */
    GPIO_REG(GPIOA_BASE, GPIO_PBC_OFF)  = PIN_LCD_CS;  /* CS = 0 */
    spi1_write_frame(dat);
    GPIO_REG(GPIOA_BASE, GPIO_PBSC_OFF) = PIN_LCD_CS;  /* CS = 1 */
}

static void lcd_init(void) {
    /* Complete GC9D01 40x160 init sequence extracted from FUN_08009b5c */
    static const uint8_t init_seq[] = {
        0xFE, 0,
        0xEF, 0,
        0x80, 1, 0xFF,  0x81, 1, 0xFF,  0x82, 1, 0xFF,  0x83, 1, 0xFF,
        0x84, 1, 0xFF,  0x85, 1, 0xFF,  0x86, 1, 0xFF,  0x87, 1, 0xFF,
        0x88, 1, 0xFF,  0x89, 1, 0xFF,  0x8A, 1, 0xFF,  0x8B, 1, 0xFF,
        0x8C, 1, 0xFF,  0x8D, 1, 0xFF,  0x8E, 1, 0xFF,  0x8F, 1, 0xFF,
        0x3A, 1, 0x05,
        0xEC, 1, 0x11,
        0x7E, 1, 0x7A,
        0x74, 7, 0x02, 0x0E, 0x00, 0x00, 0x28, 0x00, 0x00,
        0x98, 1, 0x3E,
        0x99, 1, 0x3E,
        0xB5, 2, 0x0E, 0x0E,
        0x60, 4, 0x38, 0x09, 0x6D, 0x67,
        0x63, 5, 0x38, 0xAD, 0x6D, 0x67, 0x05,
        0x64, 6, 0x38, 0x0B, 0x70, 0xAB, 0x6D, 0x67,
        0x66, 6, 0x38, 0x0F, 0x70, 0xAF, 0x6D, 0x67,
        0x6A, 2, 0x00, 0x00,
        0x68, 7, 0x3B, 0x08, 0x04, 0x00, 0x04, 0x64, 0x67,
        0x6C, 7, 0x22, 0x02, 0x22, 0x02, 0x22, 0x22, 0x50,
        0x6E, 32,
            0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x13, 0x11,
            0x0B, 0x09, 0x16, 0x15, 0x1D, 0x1E, 0x00, 0x00,
            0x00, 0x00, 0x1E, 0x1D, 0x15, 0x16, 0x0A, 0x0C,
            0x12, 0x14, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00,
        0xA9, 1, 0x1B,
        0xA8, 1, 0x6B,
        0xA8, 1, 0x6D,
        0xA7, 1, 0x40,
        0xAD, 1, 0x47,
        0xAF, 1, 0x73,
        0xAF, 1, 0x73,
        0xAC, 1, 0x44,
        0xA3, 1, 0x6C,
        0xCB, 1, 0x00,
        0xCD, 1, 0x22,
        0xC2, 1, 0x10,
        0xC5, 1, 0x00,
        0xC6, 1, 0x0E,
        0xC7, 1, 0x1F,
        0xC8, 1, 0x0E,
        0xBF, 1, 0x00,
        0xF9, 1, 0x20,
        0x9B, 1, 0x3B,
        0x93, 3, 0x33, 0x7F, 0x00,
        0x70, 6, 0x0E, 0x0F, 0x03, 0x0E, 0x0F, 0x03,
        0x71, 3, 0x0E, 0x16, 0x03,
        0x91, 2, 0x0E, 0x09,
        0xC3, 1, 0x2C,
        0xC4, 1, 0x1A,
        0xF0, 6, 0x51, 0x13, 0x0C, 0x06, 0x00, 0x2F,
        0xF2, 6, 0x51, 0x13, 0x0C, 0x06, 0x00, 0x33,
        0xF1, 6, 0x3C, 0x94, 0x4F, 0x33, 0x34, 0xCF,
        0xF3, 6, 0x4D, 0x94, 0x4F, 0x33, 0x34, 0xCF,
        0x36, 1, 0x00,
        0x11, 0
    };
    uint32_t i = 0U;
    board_delay_ms(200U);
    while (i < (uint32_t)sizeof(init_seq)) {
        uint8_t cmd = init_seq[i++];
        uint8_t n = init_seq[i++];
        lcd_cmd(cmd);
        while (n-- > 0U) {
            lcd_data(init_seq[i++]);
        }
    }
    board_delay_ms(200U);
    lcd_cmd(0x29); /* Display ON */
    lcd_cmd(0x2C);
}

static void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    lcd_cmd(0x2A);
    lcd_data((uint8_t)(x0 >> 8));
    lcd_data((uint8_t)(x0 & 0xFFU));
    lcd_data((uint8_t)(x1 >> 8));
    lcd_data((uint8_t)(x1 & 0xFFU));
    lcd_cmd(0x2B);
    lcd_data((uint8_t)(y0 >> 8));
    lcd_data((uint8_t)(y0 & 0xFFU));
    lcd_data((uint8_t)(y1 >> 8));
    lcd_data((uint8_t)(y1 & 0xFFU));
    lcd_cmd(0x2C);
}

/* Match the reference's 40-column panel order, with logical Y reversed. */
static uint16_t lcd_frame[LCD_W][LCD_H];
static bool g_rotate_180 = false;

static inline void lcd_put_px(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= (int16_t)LCD_W || y < 0 || y >= (int16_t)LCD_H) {
        return;
    }
    if (g_rotate_180) {
        lcd_frame[(LCD_W - 1U) - (uint16_t)x][(uint16_t)y] = color;
    } else {
        lcd_frame[(uint16_t)x][(LCD_H - 1U) - (uint16_t)y] = color;
    }
}

static inline uint16_t rgb565_blend(uint16_t fg, uint16_t bg, uint8_t alpha4) {
    if (alpha4 == 0U) return bg;
    if (alpha4 >= 15U) return fg;
    uint32_t f_rb = (fg & 0xF81FU);
    uint32_t b_rb = (bg & 0xF81FU);
    uint32_t f_g  = (fg & 0x07E0U);
    uint32_t b_g  = (bg & 0x07E0U);
    uint32_t rb = ((f_rb * alpha4 + b_rb * (15U - alpha4)) / 15U) & 0xF81FU;
    uint32_t g  = ((f_g  * alpha4 + b_g  * (15U - alpha4)) / 15U) & 0x07E0U;
    return (uint16_t)(rb | g);
}

static void lcd_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    for (uint16_t px = x; px < x + w && px < LCD_W; px++) {
        for (uint16_t py = y; py < y + h && py < LCD_H; py++) {
            lcd_put_px((int16_t)px, (int16_t)py, color);
        }
    }
}

static void lcd_fill_round_rect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    if (w <= 0 || h <= 0) return;
    if (r * 2 > w) r = w / 2;
    if (r * 2 > h) r = h / 2;
    for (int16_t py = 0; py < h; py++) {
        int16_t dy = 0;
        if (py < r) dy = r - 1 - py;
        else if (py >= h - r) dy = py - (h - r);
        int16_t inset = 0;
        while ((inset + 1) * (inset + 1) + dy * dy <= r * r) {
            inset++;
        }
        int16_t skip = (dy > 0) ? (r - inset) : 0;
        for (int16_t px = skip; px < w - skip; px++) {
            lcd_put_px((int16_t)(x + px), (int16_t)(y + py), color);
        }
    }
}

static void lcd_stroke_round_rect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    if (w <= 1 || h <= 1) return;
    if (r * 2 > w) r = w / 2;
    if (r * 2 > h) r = h / 2;
    for (int16_t py = 0; py < h; py++) {
        int16_t dy = 0;
        if (py < r) dy = r - 1 - py;
        else if (py >= h - r) dy = py - (h - r);
        int16_t inset = 0;
        while ((inset + 1) * (inset + 1) + dy * dy <= r * r) {
            inset++;
        }
        int16_t skip = (dy > 0) ? (r - inset) : 0;
        if (py == 0 || py == h - 1) {
            for (int16_t px = skip; px < w - skip; px++) {
                lcd_put_px((int16_t)(x + px), (int16_t)(y + py), color);
            }
        } else {
            lcd_put_px((int16_t)(x + skip), (int16_t)(y + py), color);
            lcd_put_px((int16_t)(x + w - 1 - skip), (int16_t)(y + py), color);
        }
    }
}

static void lcd_fill_circle(int16_t cx, int16_t cy, int16_t r, uint16_t color) {
    for (int16_t dy = -r; dy <= r; dy++) {
        for (int16_t dx = -r; dx <= r; dx++) {
            if (dx * dx + dy * dy <= r * r) {
                lcd_put_px((int16_t)(cx + dx), (int16_t)(cy + dy), color);
            }
        }
    }
}

static void lcd_flush(void) {
    uint32_t command_mode;
    lcd_set_window(0U, 0U, LCD_H - 1U, LCD_W - 1U);
    GPIO_REG(GPIOD_BASE, GPIO_PBSC_OFF) = PIN_LCD_DC;  /* DC = 1 */
    GPIO_REG(GPIOA_BASE, GPIO_PBC_OFF)  = PIN_LCD_CS;  /* CS = 0 */
    /* The reference sends commands in 8-bit mode and RGB565 in 16-bit mode. */
    command_mode = SPI1_CTRL1 & ~SPI1_ENABLE;
    SPI1_CTRL1 = command_mode;
    SPI1_CTRL1 = command_mode | SPI1_FRAME_16;
    SPI1_CTRL1 = command_mode | SPI1_FRAME_16 | SPI1_ENABLE;
    for (uint16_t row = 0U; row < LCD_W; row++) {
        for (uint16_t col = 0U; col < LCD_H; col++) {
            spi1_write_frame(lcd_frame[row][col]);
        }
    }
    GPIO_REG(GPIOA_BASE, GPIO_PBSC_OFF) = PIN_LCD_CS;  /* CS = 1 */
    SPI1_CTRL1 = command_mode | SPI1_FRAME_16;
    SPI1_CTRL1 = command_mode;
    SPI1_CTRL1 = command_mode | SPI1_ENABLE;
}

/* 5x7 proportional-friendly font with uppercase, lowercase, digits & symbols */
static void font_glyph(char ch, uint8_t cols[5]) {
    static const struct { char c; uint8_t d[5]; } tbl[] = {
        {' ', {0x00,0x00,0x00,0x00,0x00}},
        {'!', {0x00,0x00,0x5F,0x00,0x00}},
        {'%', {0x23,0x13,0x08,0x64,0x62}},
        {'+', {0x08,0x08,0x3E,0x08,0x08}},
        {'-', {0x08,0x08,0x08,0x08,0x08}},
        {'.', {0x00,0x60,0x60,0x00,0x00}},
        {'/', {0x20,0x10,0x08,0x04,0x02}},
        {':', {0x00,0x36,0x36,0x00,0x00}},
        {'<', {0x08,0x14,0x22,0x41,0x00}},
        {'>', {0x00,0x41,0x22,0x14,0x08}},
        {'*', {0x06,0x09,0x09,0x06,0x00}}, /* degree symbol */
        {'0', {0x3E,0x51,0x49,0x45,0x3E}},
        {'1', {0x00,0x42,0x7F,0x40,0x00}},
        {'2', {0x42,0x61,0x51,0x49,0x46}},
        {'3', {0x21,0x41,0x45,0x4B,0x31}},
        {'4', {0x18,0x14,0x12,0x7F,0x10}},
        {'5', {0x27,0x45,0x45,0x45,0x39}},
        {'6', {0x3C,0x4A,0x49,0x49,0x30}},
        {'7', {0x01,0x71,0x09,0x05,0x03}},
        {'8', {0x36,0x49,0x49,0x49,0x36}},
        {'9', {0x06,0x49,0x49,0x29,0x1E}},
        {'A', {0x7E,0x11,0x11,0x11,0x7E}},
        {'B', {0x7F,0x49,0x49,0x49,0x36}},
        {'C', {0x3E,0x41,0x41,0x41,0x22}},
        {'D', {0x7F,0x41,0x41,0x22,0x1C}},
        {'E', {0x7F,0x49,0x49,0x49,0x41}},
        {'F', {0x7F,0x09,0x09,0x09,0x01}},
        {'G', {0x3E,0x41,0x49,0x49,0x7A}},
        {'H', {0x7F,0x08,0x08,0x08,0x7F}},
        {'I', {0x00,0x41,0x7F,0x41,0x00}},
        {'K', {0x7F,0x08,0x14,0x22,0x41}},
        {'L', {0x7F,0x40,0x40,0x40,0x40}},
        {'M', {0x7F,0x02,0x0C,0x02,0x7F}},
        {'N', {0x7F,0x04,0x08,0x10,0x7F}},
        {'O', {0x3E,0x41,0x41,0x41,0x3E}},
        {'P', {0x7F,0x09,0x09,0x09,0x06}},
        {'R', {0x7F,0x09,0x19,0x29,0x46}},
        {'S', {0x46,0x49,0x49,0x49,0x31}},
        {'T', {0x01,0x01,0x7F,0x01,0x01}},
        {'U', {0x3F,0x40,0x40,0x40,0x3F}},
        {'V', {0x1F,0x20,0x40,0x20,0x1F}},
        {'W', {0x3F,0x40,0x38,0x40,0x3F}},
        {'X', {0x63,0x14,0x08,0x14,0x63}},
        {'Y', {0x07,0x08,0x70,0x08,0x07}},
        {'a', {0x20,0x54,0x54,0x54,0x78}},
        {'b', {0x7F,0x48,0x44,0x44,0x38}},
        {'c', {0x38,0x44,0x44,0x44,0x20}},
        {'d', {0x38,0x44,0x44,0x48,0x7F}},
        {'e', {0x38,0x54,0x54,0x54,0x18}},
        {'f', {0x08,0x7E,0x09,0x01,0x02}},
        {'g', {0x0C,0x52,0x52,0x52,0x3E}},
        {'h', {0x7F,0x08,0x04,0x04,0x78}},
        {'i', {0x00,0x44,0x7D,0x40,0x00}},
        {'k', {0x7F,0x10,0x28,0x44,0x00}},
        {'l', {0x00,0x41,0x7F,0x40,0x00}},
        {'m', {0x7C,0x04,0x18,0x04,0x78}},
        {'n', {0x7C,0x08,0x04,0x04,0x78}},
        {'o', {0x38,0x44,0x44,0x44,0x38}},
        {'p', {0x7C,0x14,0x14,0x14,0x08}},
        {'r', {0x7C,0x08,0x04,0x04,0x08}},
        {'s', {0x48,0x54,0x54,0x54,0x20}},
        {'t', {0x04,0x3F,0x44,0x40,0x20}},
        {'u', {0x3C,0x40,0x40,0x20,0x7C}},
        {'v', {0x1C,0x20,0x40,0x20,0x1C}},
        {'w', {0x3C,0x40,0x30,0x40,0x3C}},
        {'x', {0x44,0x28,0x10,0x28,0x44}},
        {'y', {0x0C,0x50,0x50,0x50,0x3C}},
        {'z', {0x44,0x64,0x54,0x4C,0x44}}
    };
    uint32_t i;
    for (i = 0U; i < (uint32_t)(sizeof(tbl) / sizeof(tbl[0])); i++) {
        if (tbl[i].c == ch) {
            for (uint32_t k = 0U; k < 5U; k++) {
                cols[k] = tbl[i].d[k];
            }
            return;
        }
    }
    for (i = 0U; i < 5U; i++) {
        cols[i] = 0x00U;
    }
}

static uint16_t text_width_px(const char *s, uint8_t scale) {
    uint16_t n = 0U;
    while (s && s[n] != '\0') n++;
    if (n == 0U) return 0U;
    return (uint16_t)(n * 6U * scale - scale);
}

static void lcd_draw_text_scaled(int16_t x, int16_t y, const char *s, uint16_t fg,
                                 uint16_t bg, uint8_t scale, bool transparent) {
    while (s && *s) {
        uint8_t cols[5];
        font_glyph(*s++, cols);
        for (uint8_t cx = 0U; cx < 5U; cx++) {
            for (uint8_t cy = 0U; cy < 7U; cy++) {
                const bool on = (cols[cx] & (1U << cy)) != 0U;
                if (on || !transparent) {
                    const uint16_t c = on ? fg : bg;
                    for (uint8_t sy = 0U; sy < scale; sy++) {
                        for (uint8_t sx = 0U; sx < scale; sx++) {
                            lcd_put_px((int16_t)(x + cx * scale + sx),
                                       (int16_t)(y + cy * scale + sy), c);
                        }
                    }
                }
            }
        }
        x = (int16_t)(x + 6U * scale);
    }
}

#if T90B_ADC_TEST || T90B_TEMP_TEST || T90B_FAULT_TEST
static void lcd_draw_text(uint16_t x, uint16_t y, const char *s, uint16_t fg, uint16_t bg) {
    lcd_draw_text_scaled((int16_t)x, (int16_t)y, s, fg, bg, 1U, false);
}
#endif

static bool adc_initialized;

static bool adc1_wait(volatile uint32_t *reg, uint32_t mask, uint32_t expected) {
    for (uint32_t guard = 40000U; guard > 0U; guard--) {
        if ((*reg & mask) == expected) {
            return true;
        }
    }
    return false;
}

static bool adc1_init(void) {
    /* AHB /4 for conversions, HSI 16 MHz /16 for the ADC's 1 MHz clock. */
    const uint32_t adc_clock_mask = 0x3FFFFUL;
    RCC_CFG2 = (RCC_CFG2 & ~adc_clock_mask) | (15UL << 12) | 2UL;
    ADC1_CTRL2 = 0U;
    ADC1_CTRL3 = 3U; /* AHB clock, single-ended, 12-bit. */
    ADC1_SMPR2 = 0x001B7C06UL;
    ADC1_CTRL2 = ADC1_ON | ADC1_SW_RSEL | ADC1_RTRIG | ADC1_SW_JSEL | ADC1_JTRIG;
#if T90B_ADC_TEST
    ADC1_CTRL2 |= ADC1_VREF_ON;
#endif
    if (!adc1_wait(&ADC1_CTRL3, ADC1_READY, ADC1_READY)) {
        return false;
    }
    if (ADC1_CALFACT == 0U) {
        ADC1_CTRL2 |= ADC1_CALIBRATE;
    }
    return adc1_wait(&ADC1_CTRL2, ADC1_CALIBRATE, 0U);
}

static bool adc1_read_channel(uint8_t ch, uint16_t *sample) {
    uint32_t guard = 4000U;
    ADC1_RSEQ1 = 0U;
    ADC1_RSEQ3 = (uint32_t)ch & 0x1FU;
    ADC1_STS &= ~(1UL << 1);
    ADC1_CTRL2 |= ADC1_SW_START;
    while ((ADC1_STS & (1UL << 1)) == 0U) {
        if (guard == 0U) {
            return false;
        }
        guard--;
    }
    *sample = (uint16_t)(ADC1_DAT & 0x0FFFU);
    return true;
}

static bool adc1_read_injected(uint8_t channel, uint16_t *sample) {
    /* As in the reference, a single injected conversion uses slot 4. */
    ADC1_JSEQ = (uint32_t)channel << 15;
    ADC1_STS &= ~((1UL << 2) | (1UL << 3));
    ADC1_CTRL2 |= (1UL << 21);
    if (!adc1_wait(&ADC1_STS, 1UL << 2, 1UL << 2)) {
        return false;
    }
    *sample = (uint16_t)(ADC1_JDAT1 & 0x0FFFU);
    return true;
}
#endif

void board_set_heater_pwm(uint8_t duty_pct) {
#if T90B_HEATER_ENABLED
    uint32_t primask;
    __asm__ volatile("mrs %0, primask\n cpsid i" : "=r"(primask) :: "memory");
    if (duty_pct == 0U) {
        HEAT_TIM_MODE = HEAT_FORCE_LOW;
        pwm_request_pct = 0U;
        pwm_phase_ms = 0U;
        pwm_timeout_latched = false;
    } else if (!pwm_timeout_latched) {
#if T90B_HEAT_PROBE && !T90B_HEAT_TOGGLE_TEST
        if (pwm_request_pct == 0U) {
            pwm_pulse_start_ms = g_tick_ms;
        }
#endif
        pwm_last_update_ms = g_tick_ms;
#if T90B_HEAT_PROBE
        pwm_request_pct = duty_pct > T90B_HEAT_PROBE_MAX_DUTY ? T90B_HEAT_PROBE_MAX_DUTY : duty_pct;
#else
        pwm_request_pct = duty_pct > 100U ? 100U : duty_pct;
#endif
    }
    pwm_adc_paused = false;
    __asm__ volatile("msr primask, %0" :: "r"(primask) : "memory");
#else
    (void)duty_pct;
#endif
}

void board_init(void) {
    __asm__ volatile("cpsid i");

    /* Disable inherited bootloader SysTick and pending NVIC interrupts */
    SYST_CSR = 0UL;
    NVIC_ICER0 = 0xFFFFFFFFUL;
    NVIC_ICER1 = 0xFFFFFFFFUL;
    NVIC_ICER2 = 0xFFFFFFFFUL;
    NVIC_ICPR0 = 0xFFFFFFFFUL;
    NVIC_ICPR1 = 0xFFFFFFFFUL;
    NVIC_ICPR2 = 0xFFFFFFFFUL;

    SCB_VTOR = T90B_APP_BASE;

    /* Enable DMA1 (bit 0) + ADC (bit 12) */
    RCC_AHBPCLKEN |= (1UL << 0) | (1UL << 12);
    /* Enable AFIO, GPIOA/B/D, SPI1 and the heater timer. */
    RCC_APB2PCLKEN |= (1UL << 0) | (1UL << 2) | (1UL << 3) | (1UL << 5) | (1UL << 12);
    __asm__ volatile("dsb");
#if T90B_HEATER_ENABLED || T90B_HEATER_OFF_TEST
    RCC_APB1PCLKEN |= 1U;
    __asm__ volatile("dsb");

    /* Take ownership of PA0 only after the timer is driving the off level. */
    HEAT_TIM_MODE = HEAT_FORCE_LOW;
    HEAT_TIM_CTRL1 = 0U;
    HEAT_TIM_PSC = 0U;
    HEAT_TIM_ARR = HEAT_PERIOD_TICKS - 1U;
    HEAT_TIM_CCR = HEAT_CARRIER_HIGH_TICKS;
    HEAT_TIM_EVT = 1U;
    HEAT_TIM_CCEN = 1U;
    HEAT_TIM_CTRL1 = 1U;
    gpio_config_pin(GPIOA_BASE, 0U, 2U, 1U, 2U);
#endif

#if T90B_MINIMAL_BOOT_TEST
    /* Minimal safe bring-up: PA6 backlight ON, IWDG reload, no SPI/ADC/SysTick */
    gpio_config_pin(GPIOA_BASE, 6U, 1U, 0U, 0U);
    GPIO_REG(GPIOA_BASE, GPIO_PBC_OFF) = PIN_LCD_BL;  /* BL on */
    IWDG_KEY = 0x5555U;
    IWDG_PREDIV = 6U;
    IWDG_RELV = 1000U;
    IWDG_KEY = 0xAAAAU;
    IWDG_KEY = 0xCCCCU;
    return;
#else
    /* Configure SysTick for 1 ms assuming 16 MHz HSI default if unconfigured */
    SYST_RVR = 16000UL - 1UL;
    SYST_CVR = 0UL;
    SYST_CSR = 7UL;
    __asm__ volatile("cpsie i");

    /* Factory board identification, FUN_080123a8. */
    gpio_config_pin(GPIOA_BASE, 13U, 0U, 2U, 15U);
    gpio_config_pin(GPIOA_BASE, 14U, 0U, 2U, 15U);
    uint32_t straps = GPIO_REG(GPIOA_BASE, 0x10U);
    tip_group = straps & (1U << 13) ? 0U : (straps & (1U << 14) ? 2U : 1U);
    /* Buttons: PA15 (Btn A), PB4 (Btn B) input pull-up */
    gpio_config_pin(GPIOA_BASE, 15U, 0U, 1U, 0U);
    gpio_config_pin(GPIOB_BASE, 4U, 0U, 1U, 0U);

    /* LCD pins: PA6 BL (active low), PA10 CS (idle high), PD0 DC */
    gpio_config_pin(GPIOA_BASE, 6U, 1U, 0U, 0U);
    gpio_config_pin(GPIOA_BASE, 10U, 1U, 0U, 0U);
    gpio_config_pin(GPIOD_BASE, 0U, 1U, 0U, 0U);
    GPIO_REG(GPIOA_BASE, GPIO_PBSC_OFF) = PIN_LCD_CS;  /* CS high */
    GPIO_REG(GPIOD_BASE, GPIO_PBSC_OFF) = PIN_LCD_DC;  /* DC high */
    GPIO_REG(GPIOA_BASE, GPIO_PBC_OFF)  = PIN_LCD_BL;  /* BL on */

    /* SPI1 pins: PB3 SCK (AF1), PB5 MOSI (AF0), 1-line TX Mode 3 (FUN_08009a64) */
    gpio_config_pin(GPIOB_BASE, 3U, 2U, 0U, 1U);
    gpio_config_pin(GPIOB_BASE, 5U, 2U, 0U, 0U);
    SPI1_I2SCFGR &= ~(1UL << 11);
    SPI1_CTRL1 = 0xC307U; /* 1-line TX, SSM+SSI, master, mode 3, 8-bit commands */
    SPI1_CTRL2 = 0U;
    SPI1_CTRL1 |= SPI1_ENABLE;

    /* ADC1 pins PA1..PA5 analog */
    gpio_config_pin(GPIOA_BASE, 1U, 3U, 0U, 0U);
    gpio_config_pin(GPIOA_BASE, 2U, 3U, 0U, 0U);
    gpio_config_pin(GPIOA_BASE, 3U, 3U, 0U, 0U);
    gpio_config_pin(GPIOA_BASE, 4U, 3U, 0U, 0U);
    gpio_config_pin(GPIOA_BASE, 5U, 3U, 0U, 0U);
    adc_initialized = adc1_init();



    lcd_init();
    lcd_flush();

    /* Start IWDG after LCD init (prescaler /256, reload 1000 ~ 6.4s) */
    IWDG_KEY = 0x5555U;
    IWDG_PREDIV = 6U;
    IWDG_RELV = 1000U;
    IWDG_KEY = 0xAAAAU;
    IWDG_KEY = 0xCCCCU;
#endif
}

void board_watchdog_reload(void) {
    IWDG_KEY = 0xAAAAU;
}

uint32_t board_millis(void) {
    return g_tick_ms;
}

void board_delay_ms(uint32_t ms) {
    uint32_t start = g_tick_ms;
    uint32_t guard = ms * 4000U + 1000U;
    while (((g_tick_ms - start) < ms) && (guard-- > 0U)) {
        __asm__ volatile("nop");
    }
}

#if !T90B_MINIMAL_BOOT_TEST
static btn_event_t poll_button(bool down, uint32_t now, bool *prev_down, uint32_t *down_ms, bool *long_sent) {
    btn_event_t ev = BTN_NONE;
    if (down && !(*prev_down)) {
        *down_ms = now;
        *long_sent = false;
    } else if (down && *prev_down && !(*long_sent) && ((now - *down_ms) >= 600U)) {
        *long_sent = true;
        ev = BTN_LONG;
    } else if (!down && *prev_down) {
        if (!(*long_sent) && ((now - *down_ms) >= 30U)) {
            ev = BTN_SHORT;
        }
    }
    *prev_down = down;
    return ev;
}
#endif

void board_poll_inputs(btn_event_t *btn_a, btn_event_t *btn_b, uint32_t *faults,
                       int16_t *tip_temp_dc, uint16_t *vin_mv, bool *motion) {
#if T90B_MINIMAL_BOOT_TEST
    if (btn_a) *btn_a = BTN_NONE;
    if (btn_b) *btn_b = BTN_NONE;
    if (faults) *faults = FAULT_NONE;
    if (tip_temp_dc) *tip_temp_dc = 250;
    if (vin_mv) *vin_mv = 20000U;
    if (motion) *motion = false;
    return;
#else
    static bool prev_a = false, prev_b = false, long_a = false, long_b = false;
    static uint32_t down_a = 0U, down_b = 0U;
    static bool chord_active, chord_sent;
    static uint32_t chord_start;
    const bool a_down = (GPIO_REG(GPIOA_BASE, 0x10U) & PIN_BTN_A) == 0U;
    const bool b_down = (GPIO_REG(GPIOB_BASE, 0x10U) & PIN_BTN_B) == 0U;
    const uint32_t now = g_tick_ms;
    btn_event_t event_a = BTN_NONE, event_b = BTN_NONE;
    uint16_t raw_vin;
    uint16_t raw_ntc;
    uint16_t raw_tip;
    uint32_t f = FAULT_NONE;

    /* Recognize overlap and consume both releases as one action. */
    if (a_down && b_down && !chord_active) {
        chord_active = true;
        chord_sent = false;
        chord_start = now;
        prev_a = false;
        prev_b = false;
    }
    if (chord_active) {
        if (!chord_sent && now - chord_start >= 30U) {
            event_a = BTN_SHORT;
            event_b = BTN_SHORT;
            chord_sent = true;
        }
        if (!a_down && !b_down) {
            chord_active = false;
        }
    } else {
        event_a = poll_button(a_down, now, &prev_a, &down_a, &long_a);
        event_b = poll_button(b_down, now, &prev_b, &down_b, &long_b);
    }
    if (a_down && !b_down && !long_a && !chord_active) {
        uint32_t el = now - down_a;
        g_hold_btn = 1U;
        g_hold_pct = (el >= 600U) ? 100U : (uint8_t)((el * 100U) / 600U);
    } else if (b_down && !a_down && !long_b && !chord_active) {
        uint32_t el = now - down_b;
        g_hold_btn = 2U;
        g_hold_pct = (el >= 600U) ? 100U : (uint8_t)((el * 100U) / 600U);
    } else {
        g_hold_btn = 0U;
        g_hold_pct = 0U;
    }
    if (btn_a) {
        *btn_a = event_a;
    }
    if (btn_b) {
        *btn_b = event_b;
    }

    bool settled = true;
#if T90B_HEATER_ENABLED
    /* Keep the carrier off through conversion and fault processing. */
    pwm_adc_paused = true;
    HEAT_TIM_MODE = HEAT_FORCE_LOW;
    if (pwm_request_pct != 0U) {
        const uint32_t start = board_millis();
        board_delay_ms(HEAT_ADC_SETTLE_TICKS);
        settled = board_millis() - start >= HEAT_ADC_SETTLE_TICKS;
    }
#endif
    if (!settled || !adc_initialized || !adc1_read_injected(2U, &raw_vin) ||
        !adc1_read_channel(3U, &raw_ntc) ||
        !adc1_read_injected(4U, &raw_tip)) {
        if (faults) *faults = FAULT_SENSOR;
        if (tip_temp_dc) *tip_temp_dc = 0;
        if (vin_mv) *vin_mv = 0U;
        if (motion) *motion = false;
        return;
    }

#if T90B_ADC_TEST
    for (uint8_t channel = 0U; channel < 7U; channel++) {
        if (!adc1_read_channel(channel, &adc_samples[channel]) ||
            !adc1_read_injected(channel, &adc_injected_samples[channel])) {
            f |= FAULT_SENSOR;
            break;
        }
    }
#endif

#if T90B_TEMP_TEST
    cold_ntc_adc = raw_ntc;
    cold_tip_adc = raw_tip;
#endif

    /* The reference's voltage index 3 reads injected ADC channel 2. */
    const uint16_t measured_vin = (uint16_t)((((uint32_t)raw_vin * 0xC91UL) >> 12) * 0xB00UL >> 8);
    if (vin_mv) {
        *vin_mv = measured_vin;
    }
    if (measured_vin < 8500U) {
        f |= FAULT_VOL_LOW;
    }
    if (raw_ntc < 80U || raw_ntc > 4000U) {
        f |= FAULT_NTC;
    }
    /* The reference compares converted channel 4 against 0xC59 mV. */
    const uint16_t tip_mv = (uint16_t)(((uint32_t)raw_tip * 0xC910UL) >> 16);
    if (tip_mv >= 0xC59U) {
        f |= FAULT_TIP_MISSING;
    }

    if (tip_temp_dc) {
        *tip_temp_dc = (f & (FAULT_SENSOR | FAULT_NTC | FAULT_TIP_MISSING))
                          ? 0
                          : (int16_t)tip_temperature_dc(raw_tip, ntc_temperature_dc(raw_ntc));
    }
    if (faults) {
        *faults = f;
    }
    if (motion) {
        *motion = false;
    }
#endif
}

#if !T90B_MINIMAL_BOOT_TEST
static void fmt_u16(char *dst, uint16_t v) {
    char tmp[6];
    uint32_t n = 0U;
    if (v == 0U) {
        dst[0] = '0';
        dst[1] = '\0';
        return;
    }
    while (v > 0U && n < 5U) {
        tmp[n++] = (char)('0' + (v % 10U));
        v /= 10U;
    }
    for (uint32_t i = 0U; i < n; i++) {
        dst[i] = tmp[n - 1U - i];
    }
    dst[n] = '\0';
}
#endif

#if !T90B_MINIMAL_BOOT_TEST
/* Factory interpolation, with the reference temperature and zero offset
 * from the saved preferences of this unit (block +0x5a and +0x24). */
static int tip_temperature_dc(uint16_t raw, int ambient_dc) {
    static const int16_t degrees[3][11] = {
        {54, 102, 150, 200, 250, 298, 350, 405, 448, 499, 546},
        {60, 102, 152, 200, 246, 304, 354, 402, 452, 502, 534},
        {52, 97, 150, 196, 250, 297, 348, 400, 450, 500, 538}
    };
    static const int16_t millivolts[3][11] = {
        {33, 130, 226, 340, 450, 576, 704, 832, 960, 1088, 1216},
        {204, 428, 708, 998, 1273, 1637, 1933, 2239, 2528, 2812, 3136},
        {124, 347, 589, 818, 1077, 1310, 1562, 1800, 2050, 2280, 2830}
    };
    const int16_t *t = degrees[tip_group], *v = millivolts[tip_group];
    int mv = ((uint32_t)raw * 0xc910U) >> 16;
    int lo_v = 0, lo_t = 33;
    unsigned hi = 0;
    while (hi < 10 && mv > v[hi]) {
        lo_v = v[hi];
        lo_t = t[hi++];
    }
    return ambient_dc + (lo_t - 33) * 10 +
           (mv - lo_v) * (t[hi] - lo_t) * 10 / (v[hi] - lo_v);
}

/* Factory NTC transfer table at 0x08016236, starting at -30 C. */
static int16_t ntc_temperature_dc(uint16_t sample) {
    static const uint16_t points[] = {
        3847, 3833, 3819, 3804, 3789, 3773, 3757, 3740, 3722, 3703,
        3684, 3664, 3643, 3622, 3599, 3576, 3552, 3527, 3502, 3475,
        3448, 3420, 3390, 3360, 3329, 3298, 3265, 3231, 3197, 3162,
        3123, 3089, 3051, 3013, 2973, 2933, 2893, 2852, 2810, 2767,
        2720, 2681, 2637, 2593, 2548, 2503, 2458, 2412, 2367, 2321,
        2275, 2230, 2184, 2138, 2093, 2048, 2002, 1958, 1913, 1869,
        1825, 1782, 1739, 1697, 1655, 1614, 1573, 1533, 1494, 1455,
        1417, 1380, 1343, 1307, 1272, 1237, 1203, 1170, 1138, 1106,
        1081, 1045, 1016, 987, 959, 932, 905, 879, 854, 829,
        806, 782, 760, 738, 716, 696, 675, 656, 637, 618,
        600, 583, 566, 550, 534, 518, 503, 489, 475, 461,
        448, 435, 422, 410, 398, 387, 376, 365, 355, 345,
        335, 326, 316, 308, 299, 290, 283, 274, 267, 259,
    };
    uint16_t i = 0U;
    while (i + 1U < sizeof(points) / sizeof(points[0]) && sample < points[i]) {
        i++;
    }
    if (i == 0U || sample <= points[i]) {
        return ((int16_t)i - 30) * 10;
    }
    uint16_t span = points[i - 1U] - points[i];
    const int16_t fraction = (int16_t)((10U * (points[i - 1U] - sample) + span / 2U) / span);
    return ((int16_t)i - 31) * 10 + fraction;
}
#endif

#if T90B_FAULT_TEST
void board_render_fault_test(uint32_t faults, uint32_t trip_reason, bool armed) {
    static uint32_t last_faults = UINT32_MAX, last_trip = UINT32_MAX;
    static bool last_armed;
    if (faults == last_faults && trip_reason == last_trip && armed == last_armed) {
        return;
    }
    last_faults = faults;
    last_trip = trip_reason;
    last_armed = armed;

    char buf[16];
    lcd_fill_rect(0U, 0U, LCD_W, LCD_H, 0U);
    lcd_draw_text(6U, 4U, "FAULT", 0xFFFFU, 0U);
    fmt_u16(buf, (uint16_t)faults);
    lcd_draw_text(42U, 4U, buf, 0xFFFFU, 0U);
    lcd_draw_text(78U, 4U, "TRIP", 0xFFFFU, 0U);
    fmt_u16(buf, (uint16_t)trip_reason);
    lcd_draw_text(108U, 4U, buf, 0xFFFFU, 0U);
    lcd_draw_text(6U, 15U, armed ? "ARMED" : "DISARMED", 0xFFFFU, 0U);
    lcd_draw_text(6U, 26U, "HEATER OFF", 0xFFE0U, 0U);
    lcd_flush();
}
#endif

#if !T90B_MINIMAL_BOOT_TEST
/* Apple-inspired OLED Dark RGB565 Palette */
#define COL_BLACK    0x0000U
#define COL_CARD     0x18E3U
#define COL_CARD_DK  0x10A2U
#define COL_BORDER   0x3186U
#define COL_TRACK    0x2124U
#define COL_WHITE    0xFFFFU
#define COL_MUTED    0x8C71U
#define COL_AMBER    0xFCE1U
#define COL_AMBER_D  0x3941U
#define COL_INDIGO   0x7BDFU
#define COL_INDIGO_D 0x2108U
#define COL_GREEN    0x368BU
#define COL_GREEN_D  0x0983U
#define COL_BLUE     0x0C3FU
#define COL_BLUE_D   0x0948U
#define COL_RED      0xFA27U
#define COL_RED_D    0x2841U

static uint16_t cat_accent(uint8_t cat) {
    static const uint16_t k_acc[4] = {COL_AMBER, COL_INDIGO, COL_GREEN, COL_BLUE};
    return (cat < 4U) ? k_acc[cat] : COL_BLUE;
}

static uint16_t cat_dim(uint8_t cat) {
    static const uint16_t k_dim[4] = {COL_AMBER_D, COL_INDIGO_D, COL_GREEN_D, COL_BLUE_D};
    return (cat < 4U) ? k_dim[cat] : COL_BLUE_D;
}

static void draw_cat_icon(uint8_t cat, int16_t cx, int16_t cy, uint16_t col) {
    if (cat == 0U) {
        /* Thermal: Flame */
        lcd_fill_circle(cx, (int16_t)(cy + 1), 3, col);
        lcd_fill_rect((uint16_t)(cx - 1), (uint16_t)(cy - 4), 3U, 4U, col);
        lcd_put_px(cx, (int16_t)(cy - 5), col);
        lcd_fill_circle(cx, (int16_t)(cy + 2), 1, COL_BLACK);
    } else if (cat == 1U) {
        /* Sleep: Crescent Moon */
        lcd_fill_circle(cx, cy, 4, col);
        lcd_fill_circle((int16_t)(cx + 2), (int16_t)(cy - 1), 3, COL_BLACK);
    } else if (cat == 2U) {
        /* Power: Bolt */
        lcd_fill_rect((uint16_t)(cx - 1), (uint16_t)(cy - 4), 3U, 4U, col);
        lcd_fill_rect((uint16_t)(cx - 2), cy, 5U, 1U, col);
        lcd_fill_rect((uint16_t)(cx - 1), (uint16_t)(cy + 1), 3U, 3U, col);
        lcd_put_px((int16_t)(cx + 1), (int16_t)(cy - 5), col);
        lcd_put_px((int16_t)(cx - 1), (int16_t)(cy + 4), col);
    } else {
        /* System: Gear */
        lcd_fill_circle(cx, cy, 3, col);
        lcd_fill_circle(cx, cy, 1, COL_BLACK);
        lcd_put_px(cx, (int16_t)(cy - 4), col);
        lcd_put_px(cx, (int16_t)(cy + 4), col);
        lcd_put_px((int16_t)(cx - 4), cy, col);
        lcd_put_px((int16_t)(cx + 4), cy, col);
    }
}

static void fmt_vin_str(char *dst, uint16_t vin_mv) {
    uint16_t dv = (uint16_t)(vin_mv / 100U);
    fmt_u16(dst, (uint16_t)(dv / 10U));
    uint8_t n = 0U;
    while (dst[n] != '\0') n++;
    dst[n++] = '.';
    dst[n++] = (char)('0' + (dv % 10U));
    dst[n++] = 'V';
    dst[n] = '\0';
}

static int16_t temp_to_display(const t90b_state_t *state, int16_t temp_c) {
    if (state->prefs.temp_unit == TEMP_UNIT_F) {
        return (int16_t)((temp_c * 9) / 5 + 32);
    }
    return temp_c;
}

static void render_standby_or_heat(const t90b_state_t *state, bool is_heat, int16_t display_temp) {
    char buf[16];
    char vbuf[10];
#if T90B_HEAT_PRESETS
    const int16_t target_c = (int16_t)state->preset_c;
#else
    const int16_t target_c = (int16_t)state->prefs.setpoint_c;
#endif
    const int16_t disp_set = temp_to_display(state, target_c);
    const char *unit_str = (state->prefs.temp_unit == TEMP_UNIT_F) ? "*F" : "*C";
    int16_t t_val = display_temp;
#if T90B_HEAT_TOGGLE_TEST && !T90B_HEAT_PRESETS
    t_val = display_temp / 10;
#endif
    if (t_val < 0) t_val = 0;
    const int16_t disp_live = temp_to_display(state, t_val);
    fmt_vin_str(vbuf, state->vin_mv);

    if (state->prefs.theme == UI_THEME_DOCK) {
        /* Theme A: Apple Watch Minimal (3 non-overlapping zones: [2..42] [46..112] [115..158]) */
        const uint16_t acc = is_heat ? COL_AMBER : COL_BLUE;
        lcd_fill_round_rect(2, 3, 40, 34, 6, COL_CARD);
        lcd_draw_text_scaled(6, 6, "SET", COL_MUTED, COL_CARD, 1U, true);
        fmt_u16(buf, (uint16_t)(disp_set > 0 ? disp_set : 0));
        lcd_draw_text_scaled(6, 16, buf, acc, COL_CARD, 1U, true);
        lcd_fill_round_rect(6, 29, 32, 3, 1, COL_TRACK);
        int32_t bar_w = ((int32_t)(target_c - 100) * 32) / 350;
        if (bar_w < 3) bar_w = 3;
        if (bar_w > 32) bar_w = 32;
        lcd_fill_round_rect(6, 29, (int16_t)bar_w, 3, 1, acc);

        /* Center Hero Temp */
        fmt_u16(buf, (uint16_t)disp_live);
        lcd_draw_text_scaled(47, 6, buf, is_heat ? COL_WHITE : COL_MUTED, COL_BLACK, 3U, true);
        uint16_t tw = text_width_px(buf, 3U);
        lcd_draw_text_scaled((int16_t)(49 + tw), 7, unit_str, COL_MUTED, COL_BLACK, 1U, true);
        lcd_fill_round_rect(47, 32, 62, 4, 2, COL_CARD);
        if (is_heat && state->heater_duty_pct > 0U) {
            int16_t pw = (int16_t)((62U * state->heater_duty_pct) / 100U);
            if (pw < 3) pw = 3;
            lcd_fill_round_rect(47, 32, pw, 4, 2, COL_GREEN);
        }

        /* Right Status Pill */
        lcd_fill_round_rect(115, 3, 43, 34, 6, COL_CARD_DK);
        lcd_draw_text_scaled(119, 6, is_heat ? "HEAT" : "READY", is_heat ? COL_AMBER : COL_GREEN, COL_CARD_DK, 1U, true);
        if (is_heat) {
            fmt_u16(buf, state->heater_duty_pct);
            uint8_t n = 0U;
            while (buf[n] != '\0') n++;
            buf[n++] = '%';
            buf[n] = '\0';
            lcd_draw_text_scaled(119, 17, buf, COL_WHITE, COL_CARD_DK, 1U, true);
        } else {
            lcd_draw_text_scaled(119, 17, vbuf, COL_WHITE, COL_CARD_DK, 1U, true);
        }
        lcd_draw_text_scaled(119, 27, is_heat ? "A:OFF" : "A:ON", COL_MUTED, COL_CARD_DK, 1U, true);
    } else {
        /* Theme B: Pro Telemetry Instrument */
        lcd_fill_round_rect(2, 2, 156, 36, 6, COL_CARD_DK);
        lcd_stroke_round_rect(2, 2, 156, 36, 6, is_heat ? COL_AMBER : COL_BORDER);
        lcd_fill_round_rect(6, 5, 34, 10, 3, is_heat ? COL_AMBER_D : COL_BLUE_D);
        lcd_draw_text_scaled(9, 7, is_heat ? "PID" : "STBY", is_heat ? COL_AMBER : COL_BLUE, COL_BLACK, 1U, true);

        fmt_u16(buf, (uint16_t)disp_live);
        lcd_draw_text_scaled(6, 19, buf, COL_WHITE, COL_CARD_DK, 2U, true);

        lcd_draw_text_scaled(78, 6, "SET", COL_MUTED, COL_CARD_DK, 1U, true);
        fmt_u16(buf, (uint16_t)(disp_set > 0 ? disp_set : 0));
        lcd_draw_text_scaled(98, 6, buf, COL_AMBER, COL_CARD_DK, 1U, true);

        lcd_draw_text_scaled(124, 6, vbuf, COL_GREEN, COL_CARD_DK, 1U, true);

        lcd_draw_text_scaled(78, 17, "PWM", COL_MUTED, COL_CARD_DK, 1U, true);
        fmt_u16(buf, state->heater_duty_pct);
        lcd_draw_text_scaled(98, 17, buf, COL_WHITE, COL_CARD_DK, 1U, true);
        lcd_draw_text_scaled(124, 17, "A+B", COL_MUTED, COL_CARD_DK, 1U, true);

        lcd_fill_round_rect(78, 29, 75, 4, 2, COL_TRACK);
        if (is_heat && state->heater_duty_pct > 0U) {
            int16_t pw = (int16_t)((75U * state->heater_duty_pct) / 100U);
            if (pw < 3) pw = 3;
            lcd_fill_round_rect(78, 29, pw, 4, 2, COL_GREEN);
        }
    }
}

static void render_fault_screen(uint32_t faults) {
    const char *title = "FAULT";
    if (faults & FAULT_THERMAL) title = "HEAT ERR";
    else if (faults & (FAULT_SENSOR | FAULT_NTC)) title = "ADC OPEN";
    else if (faults & FAULT_TIP_MISSING) title = "NO TIP";
    else if (faults & FAULT_VOL_LOW) title = "VOL LOW";

    lcd_fill_round_rect(3, 3, 154, 34, 7, COL_RED_D);
    lcd_stroke_round_rect(3, 3, 154, 34, 7, COL_RED);
    lcd_fill_circle(19, 20, 8, COL_RED);
    lcd_draw_text_scaled(17, 17, "!", COL_BLACK, COL_RED, 1U, true);
    lcd_draw_text_scaled(34, 9, title, COL_WHITE, COL_RED_D, 1U, true);
    lcd_draw_text_scaled(34, 22, "HEATER OFF", COL_AMBER, COL_RED_D, 1U, true);
}

static void render_menu_screen(const t90b_state_t *state, int16_t dock_w[4], int16_t list_scroll_q8) {
    char vbuf[16];
    if (state->prefs.theme == UI_THEME_DOCK && state->menu_in_dock) {
        int16_t total_w = 9;
        for (uint8_t i = 0U; i < 4U; i++) total_w = (int16_t)(total_w + (dock_w[i] >> 4));
        int16_t x = (int16_t)((LCD_W - total_w) / 2);

        for (uint8_t i = 0U; i < 4U; i++) {
            const int16_t w = (int16_t)(dock_w[i] >> 4);
            const bool act = (i == state->menu_cat);
            const int16_t y = act ? 4 : 6;
            const int16_t h = act ? 32 : 28;
            const uint16_t acc = cat_accent(i);
            const uint16_t dim = cat_dim(i);

            lcd_fill_round_rect(x, y, w, h, 7, act ? COL_CARD : COL_CARD_DK);
            if (act && g_hold_btn == 2U && g_hold_pct > 4U) {
                int16_t hw = (int16_t)((w * g_hold_pct) / 100U);
                if (hw > 2) lcd_fill_round_rect(x, y, hw, h, 6, dim);
            }
            lcd_stroke_round_rect(x, y, w, h, 7, act ? acc : COL_BORDER);

            if (act) {
                lcd_fill_round_rect((int16_t)(x + 5), (int16_t)(y + 6), 16, 20, 4, dim);
                draw_cat_icon(i, (int16_t)(x + 13), (int16_t)(y + 16), acc);
                if (w > 54) {
                    lcd_draw_text_scaled((int16_t)(x + 25), (int16_t)(y + 7), ui_cat_name(i), COL_WHITE, COL_CARD, 1U, true);
                    ui_format_item_value(state, ui_cat_flat_index(i, 0U), vbuf, (uint8_t)sizeof(vbuf));
                    lcd_draw_text_scaled((int16_t)(x + 25), (int16_t)(y + 18), vbuf, COL_MUTED, COL_CARD, 1U, true);
                }
            } else {
                draw_cat_icon(i, (int16_t)(x + w / 2), (int16_t)(y + h / 2), COL_MUTED);
            }
            x = (int16_t)(x + w + 3);
        }
    } else {
        const bool is_stack = (state->prefs.theme == UI_THEME_STACK);
        const uint8_t count = is_stack ? 14U : ui_cat_item_count(state->menu_cat);
        const uint8_t active_local = is_stack ? state->menu_index : state->menu_item;
        const uint16_t acc = cat_accent(state->menu_cat);
        const uint16_t dim = cat_dim(state->menu_cat);

        if (!is_stack) {
            lcd_fill_round_rect(2, 4, 4, 32, 2, (g_hold_btn == 1U) ? COL_WHITE : acc);
        }

        for (uint8_t i = 0U; i < count; i++) {
            const int32_t rel_q8 = ((int32_t)i << 8) - list_scroll_q8;
            if (rel_q8 < -320 || rel_q8 > 320) continue;

            const int16_t cy = (int16_t)(20 + ((rel_q8 * 24) >> 8));
            const int32_t abs_rel = (rel_q8 < 0) ? -rel_q8 : rel_q8;
            const bool focused = (abs_rel < 128);
            const int16_t card_x = (int16_t)((is_stack ? 3 : 9) + (focused ? 0 : 4));
            const int16_t card_w = (int16_t)((is_stack ? 149 : 143) - (focused ? 0 : 8));
            const int16_t card_h = focused ? 26 : 16;
            const int16_t card_y = (int16_t)(cy - card_h / 2);

            const uint8_t flat = is_stack ? i : ui_cat_flat_index(state->menu_cat, i);
            const ui_menu_item_t *meta = ui_menu_item_info(flat);

            if (focused) {
                lcd_fill_round_rect(card_x, card_y, card_w, card_h, 6, COL_CARD);
                if (g_hold_pct > 4U) {
                    int16_t hw = (int16_t)((card_w * g_hold_pct) / 100U);
                    uint16_t hc = (g_hold_btn == 1U) ? COL_RED_D : dim;
                    if (hw > 2) lcd_fill_round_rect(card_x, card_y, hw, card_h, 6, hc);
                }
                lcd_stroke_round_rect(card_x, card_y, card_w, card_h, 6, state->menu_editing ? acc : COL_BORDER);
                if (is_stack) {
                    draw_cat_icon(meta->cat, (int16_t)(card_x + 10), cy, cat_accent(meta->cat));
                }
            }

            const int16_t lx = (int16_t)(card_x + (is_stack && focused ? 20 : 6));
            lcd_draw_text_scaled(lx, (int16_t)(cy - 3), meta->label, focused ? COL_WHITE : COL_MUTED, COL_BLACK, 1U, true);

            if (focused) {
                ui_format_item_value(state, flat, vbuf, (uint8_t)sizeof(vbuf));
                const uint16_t right_edge = (uint16_t)(card_x + card_w - 5);
                if (meta->type == MENU_ITEM_TOGGLE) {
                    const bool on = (vbuf[0] == 'O' && vbuf[1] == 'N');
                    const int16_t sx = (int16_t)(right_edge - 20);
                    const int16_t sy = (int16_t)(cy - 5);
                    lcd_fill_round_rect(sx, sy, 20, 11, 5, on ? COL_GREEN : COL_BORDER);
                    lcd_fill_circle((int16_t)(on ? sx + 14 : sx + 5), cy, 4, COL_WHITE);
                } else {
                    const uint16_t vw = text_width_px(vbuf, 1U);
                    const int16_t pad = state->menu_editing ? 9 : 5;
                    const int16_t pw = (int16_t)(vw + pad * 2);
                    const int16_t px = (int16_t)(right_edge - pw);
                    const uint16_t item_col = cat_accent(meta->cat);
                    lcd_fill_round_rect(px, (int16_t)(cy - 7), pw, 15, 4, state->menu_editing ? item_col : COL_TRACK);
                    if (state->menu_editing) {
                        lcd_draw_text_scaled((int16_t)(px + 2), (int16_t)(cy - 3), "<", COL_BLACK, item_col, 1U, true);
                        lcd_draw_text_scaled((int16_t)(px + pw - 7), (int16_t)(cy - 3), ">", COL_BLACK, item_col, 1U, true);
                        lcd_draw_text_scaled((int16_t)(px + pad), (int16_t)(cy - 3), vbuf, COL_BLACK, item_col, 1U, true);
                    } else {
                        const uint16_t tc = (meta->type == MENU_ITEM_ACTION) ? COL_RED : item_col;
                        lcd_draw_text_scaled((int16_t)(px + pad), (int16_t)(cy - 3), vbuf, tc, COL_TRACK, 1U, true);
                    }
                }
            }
        }

        /* Minimal Apple Watch Capsule Scrollbar */
        lcd_fill_round_rect(155, 6, 3, 28, 1, COL_TRACK);
        int16_t thumb_h = (int16_t)(28 / (count > 0U ? count : 1U));
        if (thumb_h < 5) thumb_h = 5;
        int16_t thumb_y = 6;
        if (count > 1U) {
            thumb_y = (int16_t)(6 + ((int32_t)active_local * (28 - thumb_h)) / (count - 1U));
        }
        lcd_fill_round_rect(155, thumb_y, 3, thumb_h, 1, acc);
    }
}
#endif

void board_render_ui(const t90b_state_t *state) {
#if T90B_MINIMAL_BOOT_TEST
    (void)state;
    return;
#else
    static ui_screen_t last_screen = (ui_screen_t)255;
    static int16_t last_temp = -999;
    static uint32_t last_faults = 0xFFFFFFFFUL;
    static uint8_t last_menu = 255U;
    static uint8_t last_cat = 255U;
    static uint8_t last_duty = 255U;
    static uint8_t last_hold = 255U;
    static uint8_t last_toast = 0U;
    static bool last_dock = true;
    static bool last_edit = false;
    static uint8_t last_theme = 255U;
    static int16_t dock_w_q4[4] = {86 << 4, 20 << 4, 20 << 4, 20 << 4};
    static int16_t list_scroll_q8 = 0;

    if (T90B_LCD_TEST) {
        static bool pattern_drawn;
        if (!pattern_drawn) {
            lcd_fill_rect(8U, 8U, 40U, 24U, 0xF800U);
            lcd_fill_rect(60U, 8U, 40U, 24U, 0x07E0U);
            lcd_fill_rect(112U, 8U, 40U, 24U, 0x001FU);
            lcd_fill_rect(10U, 2U, 8U, 4U, 0xFFFFU);
            lcd_flush();
            pattern_drawn = true;
        }
        return;
    }

    if (!state) {
        return;
    }
    g_rotate_180 = (state->prefs.rotate_180 != 0U);

#if T90B_ADC_TEST || T90B_TEMP_TEST
    char buf[16];
#endif
#if T90B_ADC_TEST
    static uint32_t last_adc_frame_ms;
    static bool adc_frame_drawn;
    uint32_t now = board_millis();
    if (!adc_frame_drawn || now - last_adc_frame_ms >= 250U) {
        lcd_fill_rect(0U, 0U, LCD_W, LCD_H, 0U);
        if (state->faults & FAULT_SENSOR) {
            lcd_draw_text(6U, 6U, "SENSOR ERROR", 0xF800U, 0U);
        } else {
            for (uint16_t channel = 0U; channel < 7U; channel++) {
                const uint16_t x = (uint16_t)(6U + 78U * (channel / 4U));
                const uint16_t y = (uint16_t)(2U + 9U * (channel % 4U));
                const char label[] = {(char)('0' + channel), ':', '\0'};
                fmt_u16(buf, adc_samples[channel]);
                lcd_draw_text(x, y, label, 0xFFFFU, 0U);
                lcd_draw_text((uint16_t)(x + 15U), y, buf, 0xFFFFU, 0U);
                lcd_draw_text((uint16_t)(x + 39U), y, "/", 0xFFFFU, 0U);
                fmt_u16(buf, adc_injected_samples[channel]);
                lcd_draw_text((uint16_t)(x + 45U), y, buf, 0xFFFFU, 0U);
            }
        }
        lcd_flush();
        last_adc_frame_ms = now;
        adc_frame_drawn = true;
    }
    return;
#endif
#if T90B_TEMP_TEST
    static uint32_t last_frame_ms;
    static bool frame_drawn;
    uint32_t now = board_millis();
    if (!frame_drawn || now - last_frame_ms >= 500U) {
        lcd_fill_rect(0U, 0U, LCD_W, LCD_H, 0U);
        if (state->faults & FAULT_SENSOR) {
            lcd_draw_text(6U, 5U, "SENSOR ERROR", 0xF800U, 0U);
        } else {
            const int16_t ambient_dc = ntc_temperature_dc(cold_ntc_adc);
            const int16_t ambient = ambient_dc / 10;
            if (cold_ntc_adc == 0U || cold_ntc_adc >= 4095U) {
                lcd_draw_text(6U, 4U, "NTC ERROR", 0xF800U, 0U);
            } else {
                lcd_draw_text(6U, 4U, "NTC C", 0xFFFFU, 0U);
                if (ambient < 0) lcd_draw_text(48U, 4U, "-", 0xFFFFU, 0U);
                fmt_u16(buf, (uint16_t)(ambient < 0 ? -ambient : ambient));
                lcd_draw_text(54U, 4U, buf, 0xFFFFU, 0U);
            }
            if (cold_ntc_adc && cold_ntc_adc < 4095U &&
                !(state->faults & (FAULT_NTC | FAULT_TIP_MISSING))) {
                int tip = tip_temperature_dc(cold_tip_adc, ambient_dc) / 10;
                lcd_draw_text(80U, 4U, "TIP C", 0xFFFFU, 0U);
                if (tip < 0) lcd_draw_text(116U, 4U, "-", 0xFFFFU, 0U);
                fmt_u16(buf, (uint16_t)(tip < 0 ? -tip : tip));
                lcd_draw_text(122U, 4U, buf, 0xFFFFU, 0U);
            }
            lcd_draw_text(80U, 15U, "GROUP", 0xFFFFU, 0U);
            fmt_u16(buf, tip_group);
            lcd_draw_text(122U, 15U, buf, 0xFFFFU, 0U);
            lcd_draw_text(6U, 15U, "TIP ADC", 0xFFFFU, 0U);
            fmt_u16(buf, cold_tip_adc);
            lcd_draw_text(54U, 15U, buf, 0xFFFFU, 0U);
            lcd_draw_text(6U, 26U, "HEATER OFF", 0xFFE0U, 0U);
        }
        lcd_flush();
        last_frame_ms = now;
        frame_drawn = true;
    }
    return;
#endif

    /* Advance smooth UI springs */
    bool animating = false;
    for (uint8_t i = 0U; i < 4U; i++) {
        const int16_t target = (int16_t)((i == state->menu_cat ? 86 : 20) << 4);
        const int16_t diff = (int16_t)(target - dock_w_q4[i]);
        if (diff > 3 || diff < -3) {
            dock_w_q4[i] = (int16_t)(dock_w_q4[i] + (diff >> 1));
            animating = true;
        } else {
            dock_w_q4[i] = target;
        }
    }
    const uint8_t target_idx = (state->prefs.theme == UI_THEME_STACK) ? state->menu_index : state->menu_item;
    const int16_t target_scroll_q8 = (int16_t)((int16_t)target_idx << 8);
    const int16_t sdiff = (int16_t)(target_scroll_q8 - list_scroll_q8);
    if (sdiff > 6 || sdiff < -6) {
        list_scroll_q8 = (int16_t)(list_scroll_q8 + (sdiff >> 1));
        animating = true;
    } else {
        list_scroll_q8 = target_scroll_q8;
    }

#if T90B_HEAT_PRESETS
    const int16_t display_temp = (state->tip_temp_dc + 5) / 10;
    static uint16_t last_preset;
    bool preset_changed = state->preset_c != last_preset;
    last_preset = state->preset_c;
#elif T90B_HEAT_TOGGLE_TEST
    const int16_t display_temp = state->tip_temp_dc;
    const bool preset_changed = false;
#else
    const int16_t display_temp = state->tip_temp_dc / 10;
    const bool preset_changed = false;
#endif

    if (!animating &&
        state->screen == last_screen &&
        !preset_changed &&
        display_temp == last_temp &&
        state->faults == last_faults &&
        state->menu_index == last_menu &&
        state->menu_cat == last_cat &&
        state->menu_in_dock == last_dock &&
        state->menu_editing == last_edit &&
        state->prefs.theme == last_theme &&
        state->heater_duty_pct == last_duty &&
        g_hold_pct == last_hold &&
        state->toast_ticks == last_toast &&
        !state->menu_editing) {
        return;
    }
    last_screen = state->screen;
    last_temp = display_temp;
    last_faults = state->faults;
    last_menu = state->menu_index;
    last_cat = state->menu_cat;
    last_dock = state->menu_in_dock;
    last_edit = state->menu_editing;
    last_theme = state->prefs.theme;
    last_duty = state->heater_duty_pct;
    last_hold = g_hold_pct;
    last_toast = state->toast_ticks;

    lcd_fill_rect(0U, 0U, LCD_W, LCD_H, COL_BLACK);
    if (state->screen == UI_SCREEN_BOOT_LOGO) {
        lcd_fill_round_rect(6, 5, 148, 30, 8, COL_CARD);
        lcd_stroke_round_rect(6, 5, 148, 30, 8, COL_BLUE);
        lcd_draw_text_scaled(26, 12, "T90B", COL_WHITE, COL_CARD, 2U, true);
        lcd_draw_text_scaled(86, 16, "OPEN", COL_AMBER, COL_CARD, 1U, true);
    } else if (state->screen == UI_SCREEN_MENU) {
        render_menu_screen(state, dock_w_q4, list_scroll_q8);
    } else if (state->faults != FAULT_NONE) {
        render_fault_screen(state->faults);
    } else if (state->screen == UI_SCREEN_SLEEP) {
        char tbuf[10];
        lcd_fill_round_rect(4, 6, 42, 28, 7, COL_INDIGO_D);
        draw_cat_icon(1U, 15, 20, COL_INDIGO);
        lcd_draw_text_scaled(23, 17, "ZZZ", COL_INDIGO, COL_INDIGO_D, 1U, true);
        fmt_u16(tbuf, (uint16_t)temp_to_display(state, (int16_t)state->prefs.sleep_temp_c));
        lcd_draw_text_scaled(56, 10, tbuf, COL_MUTED, COL_BLACK, 3U, true);
    } else if (state->screen == UI_SCREEN_SETPOINT) {
        char sbuf[10];
        const int16_t sp = (int16_t)state->prefs.setpoint_c;
        lcd_fill_round_rect(2, 2, 156, 36, 7, COL_CARD);
        lcd_stroke_round_rect(2, 2, 156, 36, 7, COL_AMBER);
        lcd_draw_text_scaled(8, 6, "SET", COL_AMBER, COL_CARD, 1U, true);
        lcd_draw_text_scaled(8, 19, "<A", COL_MUTED, COL_CARD, 1U, true);
        lcd_draw_text_scaled(139, 19, "B>", COL_MUTED, COL_CARD, 1U, true);
        fmt_u16(sbuf, (uint16_t)temp_to_display(state, sp));
        lcd_draw_text_scaled(54, 10, sbuf, COL_WHITE, COL_CARD, 2U, true);
        lcd_fill_round_rect(8, 32, 144, 3, 1, COL_TRACK);
        int32_t bw = ((int32_t)(sp - 100) * 144) / 350;
        if (bw < 4) bw = 4;
        if (bw > 144) bw = 144;
        lcd_fill_round_rect(8, 32, (int16_t)bw, 3, 1, COL_AMBER);
    } else {
        const bool is_heat = (state->screen == UI_SCREEN_MAIN_HEAT);
        render_standby_or_heat(state, is_heat, display_temp);
    }

    if (state->toast_ticks > 0U && state->toast_msg && state->toast_msg[0] != '\0') {
        const uint16_t tw = text_width_px(state->toast_msg, 1U);
        const int16_t pw = (int16_t)(tw + 16U);
        const int16_t px = (int16_t)((LCD_W - pw) / 2);
        lcd_fill_round_rect(px, 11, pw, 18, 8, COL_CARD);
        lcd_stroke_round_rect(px, 11, pw, 18, 8, COL_GREEN);
        lcd_draw_text_scaled((int16_t)(px + 8), 17, state->toast_msg, COL_WHITE, COL_CARD, 1U, true);
    }

    lcd_flush();
#endif
}
