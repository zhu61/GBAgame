#include "myLib.h"
#include "DMA.h"


unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, u16 color)
{
    videoBuffer[OFFSET(row,col,240)] = color;
}

void drawBackground(const u16 *image) {
    DMA[3].src=image;
    DMA[3].dst=videoBuffer;
    DMA[3].cnt=38400|DMA_ON;
}

void drawRect(int row, int col, int height, int width, u16 color)
{
    for(int r=0; r<height; r++)
    {
        for(int c=0; c<width; c++)
        {
            setPixel(row+r, col+c, color);
        }
    }
}

void drawImage3(int r, int c, int width, int height, const u16* image)
{
    for (int i=0; i<height; i++) {
        DMA[3].src=image+i*width;
        DMA[3].dst=&videoBuffer[OFFSET(r+i,c, 240)];
        DMA[3].cnt=(width)|DMA_ON;
    }
}

void drawRiver()
{   
    DMA[3].src = BLACK;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (160 * 240) | DMA_ON | DMA_SOURCE_FIXED;
}

int boundsCheck(int *var, int bound, int *dt, int size)
{
        if(*var < 0)
        {
            *var = 0;
            *dt = -*dt;
            return 1;
        }
        if(*var > bound-size+1)
        {
            *var = bound-size+1;
            *dt = -*dt;
        }
        return 0;
}


void WaitForVblank()
{
    while(SCANLINECOUNTER > 160);
    while(SCANLINECOUNTER < 160);
}