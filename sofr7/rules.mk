# MCU name
MCU = RP2040
BOOTLOADER = rp2040

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes          # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no          # Audio output
USE_I2C = yes

# Custom matrix implementation for PCA9505
CUSTOM_MATRIX = yes
SPLIT_KEYBOARD = no

# Source files
SRC_FOLDERS += src
SRC += src/matrix.c
SRC += src/matrix_arrays.c
SRC += src/sofr7.c
SRC += src/pca9505.c
QUANTUM_LIB_SRC += i2c_master.c

# Enable I2C for PCA9505 communication
SERIAL_DRIVER = vendor
I2C_DRIVER = vendor

# Debug options
VERBOSE = yes
DEBUG_MATRIX = yes
CONSOLE_ENABLE = yes
# Optimize for size
OPT = s
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
