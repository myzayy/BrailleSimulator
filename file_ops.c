#include <stdio.h>
#include <string.h>
#include "file_ops.h"
#include "translator.h"
#include "braille.h"
int process_file(const char *input_path, const char *output_path) {
    // printf("DEBUG: Opening input file...\n");
    FILE *in = fopen(input_path, "r");
    if (in == NULL){
        printf("Error: Cannot open input file '%s'\n", input_path);
        return 1;
    }
    // printf("DEBUG: Opening output file...\n");

    //open output file to write wb = write binary
    FILE *out = fopen(output_path, "wb");
    if (out == NULL){
        printf("Error: Cannot create output file '%s'\n", output_path);
        fclose(in);
        return 1;
    }

    //printf("DEBUG: Writing empty header...\n");

    BrailleHeader header;

    // fill memory with null, clear memory from trash
    memset(&header, 0, sizeof(BrailleHeader));

    memcpy(header.magic, "BRL1", 4);
    header.version = 1;
    header.mode = 6;
    header.char_count = 0;

    //fwrite( FROM (adress), SIZE_OF_ELEMENT, NUMBER_OF_ELEMENTS (must be 1), IN );
    fwrite(&header, sizeof(BrailleHeader), 1, out);

    //read text letter by letter
    char c;
    uint32_t count = 0;
    //printf("DEBUG: Starting loop...\n");

    //fgetc - get 1 char from file untill end of file
    while ((c = fgetc(in)) != EOF) {
        //printf("DEBUG CHAR: '%c' (code %d)\n", c, c);

        uint8_t buffer[2];
        int bytes_written = char_to_braille(c, buffer);

        if (bytes_written > 0) {
            fwrite(buffer, sizeof(uint8_t), bytes_written, out);
            count += bytes_written;
        }

        //write one byte to output file
        //fwrite(&code, sizeof(uint8_t), 1, out);
        //count++;
    }
    // printf("DEBUG: Loop finished. Rewriting header...\n");
    header.char_count = count;

    // fseek  file seek - serach/replace
    // fseek( file, how many move, from where start)
    // SEEK_SET start from start of file
    fseek(out, 0, SEEK_SET);

    fwrite(&header, sizeof(BrailleHeader), 1, out);
    //printf("DEBUG: Closing files...\n");
    fclose(in);
    fclose(out);

    //finish
    printf("Done! Converted %d characters.\n", count);
    return 0;
}
