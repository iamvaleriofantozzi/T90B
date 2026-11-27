CC      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
OBJDUMP := arm-none-eabi-objdump
SIZE    := arm-none-eabi-size

HOST_CC ?= cc

BUILD_DIR := build
SRC_DIR   := src
INC_DIR   := include

TARGET_ELF := $(BUILD_DIR)/t90b.elf
TARGET_BIN := $(BUILD_DIR)/t90b.bin
TARGET_ATK := $(BUILD_DIR)/t90b.atk
TEST_BIN   := $(BUILD_DIR)/t90b_host_test

CFLAGS := -mcpu=cortex-m4 -mthumb -mfloat-abi=soft \
          -Os -ffreestanding -fdata-sections -ffunction-sections \
          -Wall -Wextra -Werror -std=c11 -I$(INC_DIR)

LDFLAGS := -T linker/t90b.ld -nostdlib -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/t90b.map

SRCS := $(SRC_DIR)/startup.c \
        $(SRC_DIR)/board.c \
        $(SRC_DIR)/ui.c \
        $(SRC_DIR)/heater.c \
        $(SRC_DIR)/main.c

OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean test lcd-test adc-test temp-test fault-test heat-probe heater-off-test heater-pulse heater-100-test heater-presets

all: $(TARGET_BIN) $(TARGET_ATK)

lcd-test:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/lcd-test EXTRA_CFLAGS="-DT90B_LCD_TEST=1 -DT90B_HEATER_ENABLED=0" all

adc-test:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/adc-test EXTRA_CFLAGS="-DT90B_ADC_TEST=1 -DT90B_HEATER_ENABLED=0" all

temp-test:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/temp-test EXTRA_CFLAGS="-DT90B_TEMP_TEST=1 -DT90B_HEATER_ENABLED=0" all

fault-test:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/fault-test EXTRA_CFLAGS="-DT90B_FAULT_TEST=1 -DT90B_HEATER_ENABLED=0" all

heater-off-test:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/heater-off-test EXTRA_CFLAGS="-DT90B_HEATER_OFF_TEST=1 -DT90B_HEATER_ENABLED=0" all

heater-100-test:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/heater-100-test EXTRA_CFLAGS="-DT90B_HEAT_PROBE=1 -DT90B_HEAT_TOGGLE_TEST=1 -DT90B_HEATER_ENABLED=1" all

heater-presets:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/heater-presets EXTRA_CFLAGS="-DT90B_HEAT_PROBE=1 -DT90B_HEAT_TOGGLE_TEST=1 -DT90B_HEATER_ENABLED=1 -DT90B_HEAT_PRESETS=1" all

heater-pulse:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/heater-pulse EXTRA_CFLAGS="-DT90B_HEAT_PROBE=1 -DT90B_HEATER_ENABLED=1" all

heat-probe:
	@echo "Heat probe suspended after an unexpected heating incident. Use the original firmware for recovery." >&2
	@false

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/t90b.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

$(TARGET_ELF): $(OBJS) linker/t90b.ld
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

$(TARGET_ATK): $(TARGET_BIN)
	python3 tools/pack_atk.py $< $@

test: $(BUILD_DIR)
	$(HOST_CC) -Wall -Wextra -Werror -std=c11 -I$(INC_DIR) -DHOST_TEST \
		$(SRC_DIR)/ui.c $(SRC_DIR)/heater.c tests/test_ui.c -o $(TEST_BIN)
	./$(TEST_BIN)
	$(HOST_CC) -Wall -Wextra -Werror -std=c11 -I$(INC_DIR) -DHOST_TEST -DT90B_HEATER_ENABLED=1 \
		$(SRC_DIR)/ui.c $(SRC_DIR)/heater.c tests/test_ui.c -o $(TEST_BIN)_pwm_mock
	./$(TEST_BIN)_pwm_mock

clean:
	rm -rf $(BUILD_DIR)
