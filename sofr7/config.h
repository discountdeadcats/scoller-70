// config.h
#pragma once

#define MATRIX_ROWS 6
#define MATRIX_COLS 16
#define DEBUG_MATRIX_SCAN_RATE



// I2C Configuration for PCA9505
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP7  // Xiao RP2040 I2C SCL pin
#define I2C1_SDA_PIN GP6  // Xiao RP2040 I2C SDA pin
#define I2C1_CLOCK_RATE 100000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define I2C_DRIVER I2CD1

#define I2C1_TIMINGR_PRESC 1U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH 15U
#define I2C1_TIMINGR_SCLL 51U


// We don't need MATRIX_ROW_PINS since we're using I2C expanders
// We don't need DIODE_DIRECTION since we're using direct pin mapping

// PCA9505 register definitions
#define PCA9505_INPUT_PORT0    0x00
#define PCA9505_OUTPUT_PORT0   0x08
#define PCA9505_POLARITY_PORT0 0x10
#define PCA9505_CONFIG_PORT0   0x18


