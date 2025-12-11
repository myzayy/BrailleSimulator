#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <stdint.h>

#define BRAILLE_CAPITAL 0x20  // symbol of Upper char (6)
#define BRAILLE_NUMBER  0x3C  // number symbol (3,4,5,6)

//func that accept char, buffer and return braille code
int char_to_braille(char c, uint8_t *output_buffer);


#endif // TRANSLATOR_H
