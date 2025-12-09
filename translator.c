#include "translator.h"
#include <ctype.h>

static const uint8_t BRAILLE_ALPHABET[26] = {
    0x01, // a (1)
    0x03, // b (1, 2)
    0x09, // c (1, 4)
    0x19, // d (1, 4, 5)
    0x11, // e (1, 5)
    0x0B, // f (1, 5)
    0x1B, // g (1, 2, 4, 5)
    0x13, // h (1, 2, 5)
    0x0A, // i (2, 4)
    0x1A, // j (2, 4, 5)
    0x05, // k (1, 3)
    0x07, // l (1, 2, 3)
    0x0D, // m (1, 3, 4)
    0x1D, // n (1, 3, 4, 5)
    0x15, // o (1, 3, 5)
    0x0F, // p (1, 2, 3, 4)
    0x1F, // q (1, 2, 3, 4, 5)
    0x17, // r (1, 2, 3, 5)
    0x0E, // s (2, 3, 4)
    0x1E, // t (2, 3, 4, 5)
    0x25, // u (1, 3, 6)
    0x27, // v (1, 2, 3, 6)
    0x3A, // w (2, 4, 5, 6)
    0x2D, // x (1, 3, 4, 6)
    0x3D, // y (1, 3, 4, 5, 6)
    0x35  // z (1, 3, 5, 6)

};

uint8_t char_to_braille(char c) {
    // if it space return 0 empty cell
    if (c == ' '){
        return 0x00;
    }

    if (isalpha(c)){
        char lower_c = tolower(c);
        // int - 'a' to take 0-25 int
        int index = lower_c - 'a';
        return BRAILLE_ALPHABET[index];
    }

    return 0x00;


}
