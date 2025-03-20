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
        {0x20, 2, 7},  // K1  - ESC
        {0x20, 2, 6},  // K2  - F1
        {0x20, 2, 5},  // K3  - F2
        {0x20, 2, 4},  // K4  - F3
        {0x20, 4, 7},  // K5  - F4
        {0x20, 4, 6},  // K6  - F5
        {0x20, 4, 5},  // K7  - F6
        {0x20, 4, 4},  // K8  - F7
        {0x20, 4, 3},  // K9  - F8
        {0x20, 4, 2},  // K10 - F9
        {0x20, 4, 1},  // K11 - F10
        {0x20, 4, 0},  // K12 - F11
        {0x20, 3, 7},  // K13 - F12
        {0x20, 3, 6},  // K14 - PrtSc
        {0x20, 3, 5},  // K15 - Pause
        {0x20, 3, 4},  // K16 - Delete
    },
    // Row 1: `, 1-0, -, =, Backspace, Home
    {
        {0x20, 3, 3},  // K17 - `
        {0x20, 3, 2},  // K18 - 1
        {0x20, 3, 1},  // K19 - 2
        {0x20, 3, 0},  // K20 - 3
        {0x20, 2, 3},  // K21 - 4
        {0x20, 2, 2},  // K22 - 5
        {0x20, 2, 1},  // K23 - 6
        {0x20, 2, 0},  // K24 - 7
        {0x20, 1, 7},  // K25 - 8
        {0x20, 1, 6},  // K26 - 9
        {0x20, 1, 5},  // K27 - 0
        {0x20, 1, 4},  // K28 - -
        {0x20, 1, 3},  // K29 - =
        {0x20, 1, 2},  // K30 - Backspace
        {0x20, 1, 1},  // K31 - home
        {0x20, 1, 0},  // K32 - tab
    },
    {
        {0x20, 0, 7},  // K33 - q
        {0x20, 0, 6},  // K34 - w
        {0x20, 0, 5},  // K35 - e
        {0x20, 0, 4},  // K36 - r
        {0x20, 0, 3},  // K37 - t
        {0x20, 0, 2},  // K38 - y
        {0x20, 0, 1},  // K39 - u
        {0x20, 0, 0},  // K40 - i
        {0x21, 2, 7},  // K41 - o
        {0x21, 2, 6},  // K42 - p
        {0x21, 2, 5},  // K43 - [
        {0x21, 2, 4},  // K44 - ]
        {0x21, 4, 7},  // K45 - slash
        {0x21, 4, 6},  // K46 - pgup   
        {0x21, 4, 5},  // K47 - capslock
        {0x21, 4, 4},  // K48 - a
    },
    // Row 3: Caps, A-L, ;, ', Enter, PgDn
    {
        {0x21, 4, 3},  // K49 - s
        {0x21,4, 2},  // K50 - d
        {0x21, 4, 1},  // K51 - f
        {0x21, 4, 0},  // K52 - g
        {0x21, 3, 7},  // K53 - h
        {0x21, 3, 6},  // K54 - j
        {0x21, 3, 5},  // K55 - k
        {0x21, 3, 4},  // K56 - l
        {0x21, 3, 3},  // K57 - ;
        {0x21, 3, 2},  // K58 - '
        {0x21, 3, 1},  // K59 - enter
        {0x21, 3, 0},  // K60 - pgdwn
        {0x21, 2, 3},  // K61 - LShift
        {0x21, 2, 2},  // K62 - z
        {0x21, 2, 1},  // K63 - x
        {0x21, 2, 0},  // K64 - c
    },

    // Row 4-5: Change 0x22 to 0x21 and 0x25 to 0x22
    // Row 4: LShift, Z-M, ,, ., /, RShift, Up, End
    {
        {0x21, 1, 7},  // K65 - v
        {0x21, 1, 6},  // K66 - b 
        {0x21, 1, 5},  // K67 - n
        {0x21, 1, 4},  // K68 - m
        {0x21, 1, 3},  // K69 - ,
        {0x21, 1, 2},  // K70 - .
        {0x21, 1, 1},  // K71 - /
        {0x21, 1, 0},  // K72 - rshift
        {0x21, 0, 7},  // K73 - up arrow
        {0x21, 0, 6},  // K74 - end
        {0x21, 0, 5},  // K75 - ctrl
        {0x21, 0, 4},  // K76 - win
        {0x21, 0, 3},  // K77 - alt
        {0x21, 0, 2},  // K78 - space
        {0x21, 0, 1},  // K79 - alt
        {0x21, 0, 0},  // K80 - fn
    },
    // Row 5: LCtrl, Win, LAlt, Space, RAlt, Fn, RCtrl, Left, Down, Right
    {
        {0x22, 0, 3},  // K81 - rctrl
        {0x22, 0, 2},  // K82 - left arrow
        {0x22, 0, 1},  // K83 - down arrow
        {0x22, 0, 0},  // K84 - right arrow
    }
};