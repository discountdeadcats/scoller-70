// config.h
#pragma once

#define MATRIX_ROWS 6
#define MATRIX_COLS 16
#define DEBUG_MATRIX_SCAN_RATE



// I2C Configuration for PCA9505
// In config.h, change:
#define USE_I2C

#define I2C_DRIVER I2CD1 
#define I2C0_SCL_PIN GP7  // Match the naming with the driver
#define I2C0_SDA_PIN GP6  // Match the naming with the driver
#define I2C1_CLOCK_RATE 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2


// We don't need MATRIX_ROW_PINS since we're using I2C expanders
// We don't need DIODE_DIRECTION since we're using direct pin mapping
#define MATRIX_IO_EXPANDER
#define MATRIX_IO_EXPANDER_I2C_ADDRESSES { 0x20, 0x22, 0x25 }  // Adjust based on scan results
// PCA9505 register definitions
#define PCA9505_INPUT_PORT0    0x00
#define PCA9505_OUTPUT_PORT0   0x08
#define PCA9505_POLARITY_PORT0 0x10
#define PCA9505_CONFIG_PORT0   0x18


