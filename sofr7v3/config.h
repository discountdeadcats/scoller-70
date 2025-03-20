// config.h
#pragma once

#define MATRIX_ROWS 6
#define MATRIX_COLS 16

// I2C configuration to match CircuitPython behavior
#define USE_I2C
#define DEBOUNCE 10  // Higher value for more stable but slower response
#define USB_POLLING_INTERVAL_MS 1  // Fastest USB polling

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP7
#define I2C1_SDA_PIN GP6
// Use CircuitPython's default 100kHz speed instead of our custom speed
#define I2C1_CLOCK_RATE 100000
// Try different duty cycle - some I2C devices are picky
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define QMK_KEYS_PER_SCAN 4  // Process multiple keys per scan