#include "media.h"
#include <stdint.h>
#include <string.h>

void create_bmp (board* the_board, char* filename) {
    int width = the_board->n_columns+0;
    int height = the_board->n_rows+0;
    int upscaling = 10;
    int size = width * height * upscaling * upscaling; // Upscaling is applied on both axis therefore, goes squared
    int width_upscaled = width * upscaling;
    int height_upscaled = height * upscaling;
    uint8_t * img = malloc(size); // Each pixel is a byte, an 8-bit unsigned integer.
    for (int row = 0 ; row < height ; row++)  // for each row
    { 
        uint8_t* current_row_ptr = img+(row*width_upscaled*upscaling);
        for(int col = 0; col < width; col++)  // for each column
        {
            uint8_t *current_col_ptr = current_row_ptr+col*upscaling;
            *(current_col_ptr) = *(the_board->cells+(row*width+col)) == 0 ? 0 : 255; // Set pixel
            for (int j = 1 ; j < upscaling ; j++) // repeat each pixel upscaling times (horizontally)
                memcpy((void*) current_col_ptr+j, (void*) current_col_ptr, sizeof(uint8_t));
        }
        for (int i = 1 ; i < upscaling ; i++) // repeat each row upscaling times (vertically)
            memcpy((void*) current_row_ptr+(i*width_upscaled), (void*) current_row_ptr, (size_t) width*upscaling);
    }
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P5\n%d %d\n255\n", width*upscaling, height*upscaling); 
    fwrite(img, 1, size, fp); // n*n pixel values, each 1 byte long.
    fclose(fp);
    free(img); 
}

