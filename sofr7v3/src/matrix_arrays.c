#include "matrix.h"

// Define the matrix arrays
matrix_row_t raw_matrix[MATRIX_ROWS] = {0};
matrix_row_t matrix[MATRIX_ROWS] = {0};

// Define the matrix access functions
matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_bin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix_get_row(row) & ((matrix_row_t)1 << col));
}
