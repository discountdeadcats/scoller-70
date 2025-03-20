#include "matrix.h"
#include "quantum.h"
#include "debug.h"
#include "wait.h"
#include "print.h"
#include "gpio.h"
#include "i2c_master.h"
#include "pca9505.h"

void matrix_init_custom(void);
bool matrix_scan_custom(matrix_row_t current_matrix[]);

void matrix_init(void) {
    // Initialize matrix
    matrix_init_custom();
    
    // Clear matrix state
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }
    
    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    bool changed = matrix_scan_custom(raw_matrix);
    
    if (changed) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = raw_matrix[row];
        }
    }
    
    matrix_scan_kb();
    return changed ? 1 : 0;
}
