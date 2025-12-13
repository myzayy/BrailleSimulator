#include <stdio.h>
#include <string.h>
#include "printer.h"
#include "braille.h"

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
    printf("-----------------\n");

    // print braille

    fseek(file, sizeof(BrailleHeader), SEEK_SET);
    uint8_t byte;
    int index = 0;

    //read by 1 byte to end of file
    while(fread(&byte, sizeof(uint8_t), 1, file) == 1) {
        printf("\n[%d] Code: 0x%02X\n", index + 1, byte);
        print_byte_as_grid(byte);
        index++;
    }

    fclose(file);
    return 0;

}
