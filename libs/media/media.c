#include "media.h"
#include <stdint.h>

void create_bmp (board* the_board, char* filename) {
    int width = the_board->n_columns+0;
    int height = the_board->n_rows+0;
    int upscaling = 10; 
    int size = width * height * upscaling * upscaling; // Upscaling is applied on both axis therefore, goes squared
    uint8_t * img = malloc(size); // Each pixel is a byte, an 8-bit unsigned integer.
    for (int row = 0 ; row < height ; row++)  // for each row
    { 
        // Maybe instead of repeting the loop I should copy memory from one place to another...
        for (int i = 0 ; i < upscaling ; i++) // repeat each row upscaling times (vertically)
        {  
            for(int col = 0; col < width; col++)  // for each column
            {
                // Maybe instead of repeting the loop I should copy memory ... again
                for (int j = 0 ; j < upscaling ; j++) // repeat each pixel upscaling times (horizontally)
                {
                    // printf("Writing [%d, %d] with data from [%d, %d]\n", (row*upscaling+i), (col*upscaling+j), row, col);
                    *(img+(upscaling*row+i)*upscaling*width+(upscaling*col+j)) = *(the_board->cells+(row*width+col)) == 0 ? 0 : 255;
                }
            }
        }
    }
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P5\n%d %d\n255\n", width*upscaling, height*upscaling); 
    fwrite(img, 1, size, fp); // n*n pixel values, each 1 byte long.
    fclose(fp);
    free(img); 
}

