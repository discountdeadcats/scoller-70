#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "gpio.h"

// Matrix state arrays
extern matrix_row_t raw_matrix[MATRIX_ROWS];
extern matrix_row_t matrix[MATRIX_ROWS];

#define MATRIX_ROW_SHIFTER ((matrix_row_t)1)

void matrix_init_custom(void);
bool matrix_scan_custom(matrix_row_t current_matrix[]);
void matrix_scan_kb(void);
void matrix_scan_user(void);
void matrix_init_kb(void);
void matrix_init_user(void);
