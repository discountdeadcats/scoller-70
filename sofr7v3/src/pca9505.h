#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"  // This includes matrix_row_t definition

// Function declarations
void matrix_init_custom(void);
bool matrix_scan_custom(matrix_row_t current_matrix[]);

// PCA9505 pin mapping structure
typedef struct {
    uint8_t chip_addr;  // I2C address of PCA9505 (0x20, 0x21, or 0x22)
    uint8_t port;       // Port number (0-4)
    uint8_t pin;        // Pin number (0-7)
} pca9505_pin_t;

// Key mapping based on the schematic where K1=ESC and K84=Right
// The pins in the schematic are IO0_0 through IO4_7 for each chip
static const pca9505_pin_t MATRIX_PIN_MAP[6][16] = {

    // Row 0: ESC, F1-F12, PrtSc, Pause, Delete
    {
        {0x20, 0, 0},  // K1  - ESC
        {0x20, 0, 1},  // K2  - F1
        {0x20, 0, 2},  // K3  - F2
        {0x20, 0, 3},  // K4  - F3
        {0x20, 0, 4},  // K5  - F4
        {0x20, 0, 5},  // K6  - F5
        {0x20, 0, 6},  // K7  - F6
        {0x20, 0, 7},  // K8  - F7
        {0x20, 1, 0},  // K9  - F8
        {0x20, 1, 1},  // K10 - F9
        {0x20, 1, 2},  // K11 - F10
        {0x20, 1, 3},  // K12 - F11
        {0x20, 1, 4},  // K13 - F12
        {0x20, 1, 5},  // K14 - PrtSc
        {0x20, 1, 6},  // K15 - Pause
        {0x20, 1, 7},  // K16 - Delete
    },
    // Row 1: `, 1-0, -, =, Backspace, Home
    {
        {0x20, 2, 0},  // K17 - `
        {0x20, 2, 1},  // K18 - 1
        {0x20, 2, 2},  // K19 - 2
        {0x20, 2, 3},  // K20 - 3
        {0x20, 2, 4},  // K21 - 4
        {0x20, 2, 5},  // K22 - 5
        {0x20, 2, 6},  // K23 - 6
        {0x20, 2, 7},  // K24 - 7
        {0x20, 3, 0},  // K25 - 8
        {0x20, 3, 1},  // K26 - 9
        {0x20, 3, 2},  // K27 - 0
        {0x20, 3, 3},  // K28 - -
        {0x20, 3, 4},  // K29 - =
        {0x20, 3, 5},  // K30 - Backspace
        {0x20, 3, 6},  // K31 - Backspace (same key)
        {0x20, 3, 7},  // K32 - Home
    },
    {
        {0x22, 0, 0},  // K33 - Tab
        {0x22, 0, 1},  // K34 - Q
        {0x22, 0, 2},  // K35 - W
        {0x22, 0, 3},  // K36 - E
        {0x22, 0, 4},  // K37 - R
        {0x22, 0, 5},  // K38 - T
        {0x22, 0, 6},  // K39 - Y
        {0x22, 0, 7},  // K40 - U
        {0x22, 1, 0},  // K41 - I
        {0x22, 1, 1},  // K42 - O
        {0x22, 1, 2},  // K43 - P
        {0x22, 1, 3},  // K44 - [
        {0x22, 1, 4},  // K45 - ]
        {0x22, 1, 5},  // K46 - backslash   
        {0x22, 1, 6},  // K47 - backslash     (same key)
        {0x22, 1, 7},  // K48 - PgUp
    },
    // Row 3: Caps, A-L, ;, ', Enter, PgDn
    {
        {0x22, 2, 0},  // K49 - Caps Lock
        {0x22, 2, 1},  // K50 - A
        {0x22, 2, 2},  // K51 - S
        {0x22, 2, 3},  // K52 - D
        {0x22, 2, 4},  // K53 - F
        {0x22, 2, 5},  // K54 - G
        {0x22, 2, 6},  // K55 - H
        {0x22, 2, 7},  // K56 - J
        {0x22, 3, 0},  // K57 - K
        {0x22, 3, 1},  // K58 - L
        {0x22, 3, 2},  // K59 - ;
        {0x22, 3, 3},  // K60 - '
        {0x22, 3, 4},  // K61 - Enter
        {0x22, 3, 5},  // K62 - Enter (same key)
        {0x22, 3, 6},  // K63 - Enter (same key)
        {0x22, 3, 7},  // K64 - PgDn
    },

    // Row 4-5: Change 0x22 to 0x25 (per your comment)
    // Row 4: LShift, Z-M, ,, ., /, RShift, Up, End
    {
        {0x25, 0, 0},  // K65 - LShift
        {0x25, 0, 1},  // K66 - LShift (same key)
        {0x25, 0, 2},  // K67 - Z
        {0x25, 0, 3},  // K68 - X
        {0x25, 0, 4},  // K69 - C
        {0x25, 0, 5},  // K70 - V
        {0x25, 0, 6},  // K71 - B
        {0x25, 0, 7},  // K72 - N
        {0x25, 1, 0},  // K73 - M
        {0x25, 1, 1},  // K74 - ,
        {0x25, 1, 2},  // K75 - .
        {0x25, 1, 3},  // K76 - /
        {0x25, 1, 4},  // K77 - RShift
        {0x25, 1, 5},  // K78 - RShift (same key)
        {0x25, 1, 6},  // K79 - Up
        {0x25, 1, 7},  // K80 - End
    },
    // Row 5: LCtrl, Win, LAlt, Space, RAlt, Fn, RCtrl, Left, Down, Right
    {
        {0x25, 2, 0},  // K81 - LCtrl
        {0x25, 2, 1},  // K82 - Win
        {0x25, 2, 2},  // K83 - LAlt
        {0x25, 2, 3},  // K84 - Space
        {0x25, 2, 4},  // K85 - Space (same key)
        {0x25, 2, 5},  // K86 - Space (same key)
        {0x25, 2, 6},  // K87 - Space (same key)
        {0x25, 2, 7},  // K88 - Space (same key)
        {0x25, 3, 0},  // K89 - Space (same key)
        {0x25, 3, 1},  // K90 - RAlt
        {0x25, 3, 2},  // K91 - Fn
        {0x25, 3, 3},  // K92 - RCtrl
        {0x25, 3, 4},  // K93 - Left
        {0x25, 3, 5},  // K94 - Down
        {0x25, 3, 6},  // K95 - Right
        {0x25, 3, 7},  // Not used
    }
};