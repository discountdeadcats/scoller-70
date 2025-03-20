#include "quantum.h"
#include "i2c_master.h"
#include "wait.h"
#include "pca9505.h"
#include "debug.h"

// ------------ Constants -------------
// PCA9505 Register addresses
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

// PCA9505 addresses used in our keyboard
#define CHIP_ADDR_0 0x20
#define CHIP_ADDR_1 0x21
#define CHIP_ADDR_2 0x22
#define CHIP_COUNT 3

// The number of ports per chip
#define PORTS_PER_CHIP 5

// Store last read data to avoid repeat reads
static uint8_t last_data[CHIP_COUNT][PORTS_PER_CHIP] = {
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // Chip 0x20
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},  // Chip 0x21
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}   // Chip 0x22
};

// Track which chips are responding
static bool chip_online[CHIP_COUNT] = {false, false, false};

// Update the read_port_data function for better reliability
static bool read_port_data(uint8_t addr, uint8_t port, uint8_t *data) {
    // First write the register we want to read from
    uint8_t reg = port;
    
    // Multiple transmission attempts for reliability
    bool success = false;
    for (int retry = 0; retry < 3 && !success; retry++) {
        success = (i2c_transmit(addr << 1, &reg, 1, 200) == I2C_STATUS_SUCCESS);
        if (!success) wait_us(100); // Small delay before retry
    }
    
    // Delay between write and read operations - important for reliability
    wait_us(200);
    
    // Then read the data from that register
    if (success) {
        success = false;
        for (int retry = 0; retry < 3 && !success; retry++) {
            success = (i2c_receive(addr << 1 | 1, data, 1, 200) == I2C_STATUS_SUCCESS);
            if (!success) wait_us(100); // Small delay before retry
        }
    }
    
    return success;
}

// Initialize the keyboard
void matrix_init_custom(void) {
    // Initialize I2C with proper parameters
    i2c_init();
    
    // Give chips time to power up and stabilize
    wait_ms(500);
    
    dprintf("Starting PCA9505 keyboard initialization\n");
    
    // Check which chips are online
    for (uint8_t i = 0; i < CHIP_COUNT; i++) {
        uint8_t addr = (i == 0) ? CHIP_ADDR_0 : (i == 1) ? CHIP_ADDR_1 : CHIP_ADDR_2;
        uint8_t data = 0xFF;
        
        dprintf("Testing chip 0x%02X... ", addr);
        
        // Try to read from port 0
        if (read_port_data(addr, PCA9505_INPUT_PORT0, &data)) {
            chip_online[i] = true;
            dprintf("ONLINE (data: 0x%02X)\n", data);
            
            // Configure all ports as inputs
            for (uint8_t port = 0; port < PORTS_PER_CHIP; port++) {
                // Set normal polarity (0 = normal, 1 = inverted)
                uint8_t polarity_reg = PCA9505_POLARITY_PORT0 + port;
                uint8_t polarity_data = 0x00;
                i2c_transmit(addr << 1, &polarity_reg, 1, 100);
                wait_ms(5);
                i2c_transmit(addr << 1, &polarity_data, 1, 100);
                wait_ms(5);
                
                // Set all pins as inputs (1 = input, 0 = output)
                uint8_t config_reg = PCA9505_CONFIG_PORT0 + port;
                uint8_t config_data = 0xFF;
                i2c_transmit(addr << 1, &config_reg, 1, 100);
                wait_ms(5);
                i2c_transmit(addr << 1, &config_data, 1, 100);
                wait_ms(5);
            }
            
            // Read all ports to cache initial state
            for (uint8_t port = 0; port < PORTS_PER_CHIP; port++) {
                read_port_data(addr, PCA9505_INPUT_PORT0 + port, &last_data[i][port]);
            }
        } else {
            chip_online[i] = false;
            dprintf("OFFLINE\n");
        }
    }
    
    dprintf("Initialization complete\n");
}

// Scan the matrix for key presses - with debugging
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_changed = false;
    static uint8_t current_port_data[CHIP_COUNT][PORTS_PER_CHIP];
    static uint32_t last_debug = 0;
    
    // Set up a debug log every 30 seconds to see what keys are being detected
    bool debug_now = false;
    if (timer_elapsed32(last_debug) > 30000) {
        debug_now = true;
        last_debug = timer_read32();
        dprintf("\n--- Key Matrix Status ---\n");
    }
    
    // Read data from each chip
    for (uint8_t i = 0; i < CHIP_COUNT; i++) {
        // Get the actual chip address from the chip index
        uint8_t addr = (i == 0) ? CHIP_ADDR_0 : (i == 1) ? CHIP_ADDR_1 : CHIP_ADDR_2;
        
        // Debug chip access status periodically
        if (debug_now) {
            dprintf("Reading chip 0x%02X: ", addr);
        }
        
        // Flag to track if this chip is accessible
        bool chip_ok = true;
        
        // Read all ports for this chip
        for (uint8_t port = 0; port < PORTS_PER_CHIP; port++) {
            // Try to read the port data
            if (read_port_data(addr, PCA9505_INPUT_PORT0 + port, &current_port_data[i][port])) {
                // Successful read, update cached data
                last_data[i][port] = current_port_data[i][port];
            } else {
                // Read failed, use cached data
                current_port_data[i][port] = last_data[i][port];
                chip_ok = false;
            }
        }
        
        // Update online status and log results
        if (chip_ok) {
            chip_online[i] = true;
            if (debug_now) dprintf("SUCCESS\n");
        } else {
            chip_online[i] = false;
            if (debug_now) dprintf("FAILED (using cached data)\n");
        }
    }
    
    // Now process the matrix with the data we read
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t current_row = 0;
        
        if (debug_now) {
            dprintf("Row %d: ", row);
        }
        
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            // Skip the undefined keys in row 5
            if (row == 5 && col >= 4) continue;
            
            // Get the chip, port, and pin for this matrix position
            const pca9505_pin_t pin_data = MATRIX_PIN_MAP[row][col];
            uint8_t chip_addr = pin_data.chip_addr;
            uint8_t port = pin_data.port;
            uint8_t pin = pin_data.pin;
            
            // Determine which chip index handles this key
            uint8_t chip_idx = 0xFF; // Invalid value to start
            if (chip_addr == CHIP_ADDR_0) {
                chip_idx = 0;
            } else if (chip_addr == CHIP_ADDR_1) {
                chip_idx = 1;
            } else if (chip_addr == CHIP_ADDR_2) {
                chip_idx = 2;
            }
            
            // Skip invalid chip indices
            if (chip_idx >= CHIP_COUNT) continue;
            
            // Get the port data and check if the key is pressed
            uint8_t port_data = current_port_data[chip_idx][port];
            bool key_pressed = !(port_data & (1 << pin));
            
            if (key_pressed) {
                current_row |= (1UL << col);
                
                // Debug log any pressed keys
                if (debug_now) {
                    dprintf("[%d,%d:0x%02X.%d.%d] ", row, col, chip_addr, port, pin);
                }
            }
        }
        
        if (debug_now) {
            dprintf("\n");
        }
        
        // Update matrix
        if (current_matrix[row] != current_row) {
            current_matrix[row] = current_row;
            matrix_changed = true;
        }
    }
    
    return matrix_changed;
}
// Diagnostic function that can be called from a custom keycode
void pca9505_debug(void) {
    dprintf("\n==== PCA9505 Debug Report ====\n");
    
    // Show chip status
    dprintf("Chip status:\n");
    dprintf("  0x%02X: %s\n", CHIP_ADDR_0, chip_online[0] ? "ONLINE" : "OFFLINE");
    dprintf("  0x%02X: %s\n", CHIP_ADDR_1, chip_online[1] ? "ONLINE" : "OFFLINE");
    dprintf("  0x%02X: %s\n", CHIP_ADDR_2, chip_online[2] ? "ONLINE" : "OFFLINE");
    
    // For each chip, show port data
    for (uint8_t i = 0; i < CHIP_COUNT; i++) {
        uint8_t addr = (i == 0) ? CHIP_ADDR_0 : (i == 1) ? CHIP_ADDR_1 : CHIP_ADDR_2;
        
        dprintf("\nChip 0x%02X port data:\n", addr);
        
        if (!chip_online[i]) {
            dprintf("  OFFLINE - using cached data\n");
        }
        
        // Read all ports
        for (uint8_t port = 0; port < PORTS_PER_CHIP; port++) {
            uint8_t data = 0xFF;
            bool read_success = false;
            
            if (chip_online[i]) {
                read_success = read_port_data(addr, PCA9505_INPUT_PORT0 + port, &data);
                if (read_success) {
                    last_data[i][port] = data; // Update cache
                } else {
                    data = last_data[i][port]; // Use cached data
                }
            } else {
                data = last_data[i][port]; // Use cached data
            }
            
            dprintf("  Port %d: 0x%02X %s\n", 
                   port, 
                   data, 
                   (chip_online[i] && read_success) ? "" : "(cached)");
        }
    }
    
    // Try a direct I2C scan
    dprintf("\nDirect I2C scan:\n");
    for (uint8_t addr = 0x08; addr < 0x78; addr++) {
        uint8_t reg = 0x00;
        if (i2c_transmit(addr << 1, &reg, 1, 10) == I2C_STATUS_SUCCESS) {
            dprintf("  Found device at 0x%02X\n", addr);
        }
    }
    
    dprintf("==== Debug Report End ====\n");
}