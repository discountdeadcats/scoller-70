#include "sofr7.h"
#include "pca9505.h"

void matrix_init_kb(void) {
    matrix_init_user();
}

void matrix_scan_kb(void) {
    matrix_scan_user();
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
    
    // Enable debugging
    debug_enable = true;
    debug_matrix = true;
}

__attribute__((weak)) void keyboard_post_init_user(void) {
}

__attribute__((weak)) void matrix_init_user(void) {
}

__attribute__((weak)) void matrix_scan_user(void) {
}
