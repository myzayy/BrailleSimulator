#include <stdio.h>
#include <string.h>
#include "braille.h"
#include "translator.h"
// braille -t input.txt output.brl


void print_help() {
    printf("Usage:\n");
    printf("  Translation: program -t input.txt output.brl\n");
    printf("  Printing:    program -p input.brl\n");
}

int main(int argc, char *argv[])
{

    // If there are not enough arguments, print help
    if (argc < 3) {
        print_help();
        return 1;
    }

    // Check first argument (flag)
    // strcmp compare two strings.
    if (strcmp(argv[1], "-t") == 0) {
        if (argc != 4) {
            printf("Error: Invalid arguments for translation.\n");
            return 1;
        }
        printf("Mode: Translation (Text -> Braille)\n");
        printf("Input: %s\n", argv[2]);
        printf("Output: %s\n", argv[3]);

        // there will be call func translate_text()
        printf("Test translation:\n");
        char test_word[] = "hello";
        for(int i = 0; i < 5; i++){
            printf("%c -> %02X\n", test_word[i], char_to_braille(test_word[i]));
        }


    } else if (strcmp(argv[1], "-p") == 0) {
        printf("Mode: Printing (Braille -> Screen)\n");
        printf("Input file: %s\n", argv[2]);

        // there will be call func print_braille()

    } else {
        printf("Error: Unknown parameter %s\n", argv[1]);
        print_help();
        return 1;
    }

    return 0;
}
