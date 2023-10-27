#include "media.h"
#include <stdint.h>

void create_bmp (board* the_board, char* filename) {
    int width = the_board->n_columns+0;
    int height = the_board->n_rows+0;
    int size = width*height;
    uint8_t * img = malloc(size); // Each pixel is a byte, an 8-bit unsigned integer.
    for(int i = 0; i < size; i++) { 
        img[i] = *(the_board->cells+i) == 0 ? 0 : 255;
    }
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P5\n%d %d\n255\n", width, height); // P5 mode for grayscale, since you don't specify in your question what you want to do with colors.
    fwrite(img, 1, size, fp); // n*n pixel values, each 1 byte long.
    fclose(fp);
    free(img); 
}

