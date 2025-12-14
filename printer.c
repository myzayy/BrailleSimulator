#include <stdio.h>
#include <string.h>
#include "printer.h"
#include "braille.h"

// braille word coun in one line
// if line will be longer, he will move lower

#define CHARS_PER_LINE 20

int count_dots_in_byte(uint8_t byte) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if ((byte >> i) & 1) {
            count++;
        }
    }
    return count;
}

void print_byte_as_grid(uint8_t code) {
    // shorted write of if/else
    // (condition) ? (value if true) : (value if false)
    // line 1 bit 0 and bit 3
    printf(" %c %c\n", (code & 0x01) ? 'O' : '.', (code & 0x08) ? 'O' : '.');
    // line 2 bit 1 and bit 4
    printf(" %c %c\n", (code & 0x02) ? 'O' : '.', (code & 0x10) ? 'O' : '.');
    // line 3 bit 2 and bit 5
    printf(" %c %c\n", (code & 0x04) ? 'O' : '.', (code & 0x20) ? 'O' : '.');
}

int print_to_braille_file(const char *file_path){

    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("Error: cannot open file '%s' to read.\n", file_path);
        return 1;
    }

    BrailleHeader header;
    // size_t is like int but smart, he can choose how many bytes he like to use, order by how many program uses. And size_t dont have -1 atd.
    size_t read_count = fread(&header, sizeof(BrailleHeader), 1, file);

    if (read_count != 1) {
        printf("Error: File is too short or empty.\n");
        fclose(file);
        return 1;
    }

    // Check Magic Number in header
    // String N Compare compare n - symbols and return 0 if they =

    if (strncmp(header.magic, "BRL1", 4) != 0) {
        printf("Error: Invalid file format. Expected 'BRL1'.\n");
        fclose(file);
        return 1;
    }

    // print results

    printf("--- File info ---\n");
    printf("Signature:  %.4s\n", header.magic);
    printf("Version:    %d\n", header.version);
    printf("Characters: %d\n", header.char_count);
    printf("---------------------------\n\n");

    // print braille
    int total_dots = 0;

    fseek(file, sizeof(BrailleHeader), SEEK_SET);
    uint8_t buffer[CHARS_PER_LINE];
    size_t bytes_read;

    //read by 1 byte to end of file
    // while(fread(&byte, sizeof(uint8_t), 1, file) == 1) {
    //     printf("\n[%d] Code: 0x%02X\n", index + 1, byte);
    //     print_byte_as_grid(byte);
    //     index++;
    // }

    while((bytes_read = fread(buffer, sizeof(uint8_t), CHARS_PER_LINE, file)) > 0) {

        for(size_t i = 0; i < bytes_read; i++){
            total_dots += count_dots_in_byte(buffer[i]);
        }

        for (size_t i = 0; i < bytes_read; i++) {
            uint8_t code = buffer[i];
            // 0x01 (bit 0), 0x08 (bit 3)
            printf("%c%c ", (code & 0x01) ? 'O' : '.', (code & 0x08) ? 'O' : '.');
        }
        printf("\n");

        for (size_t i = 0; i < bytes_read; i++) {
            uint8_t code = buffer[i];
            // 0x02 (bit 1), 0x10 (bit 4)
            printf("%c%c ", (code & 0x02) ? 'O' : '.', (code & 0x10) ? 'O' : '.');
        }
        printf("\n");

        for (size_t i = 0; i < bytes_read; i++) {
            uint8_t code = buffer[i];
            // 0x04 (bit 2), 0x20 (bit 5)
            printf("%c%c ", (code & 0x04) ? 'O' : '.', (code & 0x20) ? 'O' : '.');
        }
        printf("\n\n");
    }

    printf("---------------------------\n");
    printf("Statistic:\n");
    printf("Total characters:      %d\n", header.char_count);
    printf("Total embossed dots:   %d\n", total_dots);
    printf("---------------------------\n");

    fclose(file);
    return 0;

}
