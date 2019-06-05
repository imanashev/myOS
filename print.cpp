#include "print.h"
#include "types.h"

namespace Screen {

int xPos = 0;
int yPos = 0;
u16 *videoMemory = (u16 *)VIDEO_MEMORY;
const int screenHigh = SCREEN_HIGH;
const int screenWidth = SCREEN_WIDTH;

// Private functions declaration
void printNumHelper(int number, int color = color::white);
void tab();
void incXPos();
void incYPos();

void print(const char *string, int color)
{
    char c = string[0];
    for(int i = 1; c; ++i) {
        switch (c) {
            case 9: {
                tab();
                break;
            }
            case 10: {
                newLine();
                break;
            }
            default: {
                print(c, color);
            }
        }
        c = string[i];
    }
}

void print(char *string, int color)
{
    const char* str = string;
    print(str, color);
}

void print(int number, int color)
{
    if(number) {
        printNumHelper(number, color);
    } else {
        print('0', color);
    }
}

void print(const char symbol, int color)
{
    videoMemory[yPos * screenWidth + xPos] = symbol | (color << 8);
    incXPos();
}

void scroll(int lines)
{
    int writePos = 0;
    int readPos = lines * screenWidth;

    //memory after visible screen (screenWidth * screenHigh) must be null
    while (writePos <= screenWidth * screenHigh) {
        videoMemory[writePos++] = videoMemory[readPos++];
    }

    if (lines > yPos) {
        yPos = 0;
    } else {
        yPos = yPos - lines + 1;
    }
}

void printNumHelper(int number, int color)
{
    if(number != 0) {
        printNumHelper(number / 10, color);
        const char digit = '0' + (number % 10);
        print(digit, color);
    }
}

void newLine()
{
    incYPos();
    xPos = 0;
}

void tab()
{
    // end of screen case
    if (xPos > screenWidth - 3) {
        newLine();
        return;
    }
    int spaces = 4 - (xPos % 4);
    for (int i = 0; i < spaces; ++i) {
        print(' ');
    }
}

void incXPos()
{
    if (++xPos > screenWidth) {
        xPos = 0;
        incYPos();
    }
}

void incYPos()
{
    if(yPos < screenHigh) {
        ++yPos;
    } else {
        scroll(SCROLL_LINES);
    }
}

} // namespace Screen
