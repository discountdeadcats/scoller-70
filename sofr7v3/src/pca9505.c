#include "pca9505.h"
#include "i2c_master.h"
#include "wait.h"
#include "debug.h"
#include "print.h"
#include "quantum.h"  // Added this for matrix_row_t definition

// PCA9505 registers
#define PCA9505_INPUT_PORT0    0x00
#define PCA9505_INPUT_PORT1    0x01
#define PCA9505_INPUT_PORT2    0x02
#define PCA9505_INPUT_PORT3    0x03
#define PCA9505_INPUT_PORT4    0x04
#define PCA9505_OUTPUT_PORT0   0x08
#define PCA9505_OUTPUT_PORT1   0x09
#define PCA9505_OUTPUT_PORT2   0x0A
#define PCA9505_OUTPUT_PORT3   0x0B
#define PCA9505_OUTPUT_PORT4   0x0C
#define PCA9505_POLARITY_PORT0 0x10
#define PCA9505_POLARITY_PORT1 0x11
#define PCA9505_POLARITY_PORT2 0x12
#define PCA9505_POLARITY_PORT3 0x13
#define PCA9505_POLARITY_PORT4 0x14
#define PCA9505_CONFIG_PORT0   0x18
#define PCA9505_CONFIG_PORT1   0x19
#define PCA9505_CONFIG_PORT2   0x1A
#define PCA9505_CONFIG_PORT3   0x1B
#define PCA9505_CONFIG_PORT4   0x1C

// Initialize a single PCA9505 chip
static bool pca9505_init_chip(uint8_t addr) {
    uint8_t config_data = 0xFF;
    uint8_t polarity_data = 0x00;
    uint8_t output_data = 0xFF;
    
    // Set all ports as inputs (1 = input)
    for (uint8_t port = 0; port < 5; port++) {
        if (i2c_write_register(addr, PCA9505_CONFIG_PORT0 + port, &config_data, 1, 100) != I2C_STATUS_SUCCESS) {
            print("Failed to configure port as input\n");
            return false;
        }
        
        // Set normal polarity (0 = normal)
        if (i2c_write_register(addr, PCA9505_POLARITY_PORT0 + port, &polarity_data, 1, 100) != I2C_STATUS_SUCCESS) {
            print("Failed to set polarity\n");
            return false;
        }
        
        // Set output state high (for pull-up)
        if (i2c_write_register(addr, PCA9505_OUTPUT_PORT0 + port, &output_data, 1, 100) != I2C_STATUS_SUCCESS) {
            print("Failed to set output state\n");
            return false;
        }
    }
    return true;
}

// Read a port from PCA9505
static uint8_t pca9505_read_port(uint8_t addr, uint8_t port) {
    uint8_t data = 0xFF;
    i2c_status_t status = i2c_read_register(addr, PCA9505_INPUT_PORT0 + port, &data, 1, 100);
    if (status != I2C_STATUS_SUCCESS) {
        xprintf("I2C read failed with status: %d on addr 0x%X, port %d\n", status, addr, port);
        return 0xFF;
    }
    return data;
}

void matrix_init_custom(void) {
    // Initialize I2C with a 400kHz clock
    i2c_init();
    
    // Add a small delay for I2C to stabilize
    wait_ms(1);
    
    // Re-add first chip (0x20)
    if (!pca9505_init_chip(0x20)) print("Failed to init chip 0x20\n");
    if (!pca9505_init_chip(0x22)) print("Failed to init chip 0x22\n");
    if (!pca9505_init_chip(0x25)) print("Failed to init chip 0x25\n");
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_row_t current_row_value = 0;

        // Scan all columns in the current row
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            // Get pin mapping for this position
            pca9505_pin_t pin = MATRIX_PIN_MAP[current_row][col];
            
            // Read the port
            uint8_t port_data = pca9505_read_port(pin.chip_addr, pin.port);
            
            // Check if the key is pressed (assuming active low)
            if (!(port_data & (1 << pin.pin))) {
                current_row_value |= ((matrix_row_t)1 << col);
            }
        }

        // Check if the row has changed
        if (current_matrix[current_row] != current_row_value) {
            current_matrix[current_row] = current_row_value;
            changed = true;
        }
    }

    return changed;
}
