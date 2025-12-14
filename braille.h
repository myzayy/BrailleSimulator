#ifndef BRAILLE_H
#define BRAILLE_H

#include <stdint.h>
#define BRAILLE_NUMBER  0x3C  // (dot 3, 4, 5, 6)
#define BRAILLE_CAPITAL 0x20
// Header struct
// Takes memory sequentially
// u - unsigned 0+
//_t - type
typedef struct {
    char magic[4];       // 4 bytes: identifer (example., "BRL1")
    uint8_t version;     // 1 byte: format version
    uint8_t mode;        // 1 byte: mode (6 or 8 dotes)
    uint8_t reserved[2]; // 2 bytes
    uint32_t char_count; // 4 bytes
    uint32_t checksum;
    uint8_t padding[16]; // 16 bytes: reserve for 0-os for 32 of sum
} BrailleHeader;

//32 bytes

#endif
