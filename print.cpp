#include "print.h"

Screen::Screen() : screenHigh(SCREEN_HIGH),
            screenWidth(SCREEN_WIDTH),
            videoMemory((unsigned short *)VIDEO_MEMORY),
            xPos(0),
            yPos(0)
{}

void Screen::print(const char *string, int color)
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

    void Screen::print(int number, int color)
    {
        if(number) {
            printNumHelper(number, color);
        } else {
            print('0', color);
        }
    }

    void Screen::print(const char symbol, int color)
    {
        videoMemory[yPos * screenWidth + xPos] = symbol | (color << 8);
        incXPos();
    }

    void Screen::scroll(int lines)
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

    void Screen::printNumHelper(int number, int color)
    {
        if(number != 0) {
            printNumHelper(number / 10, color);
            const char digit = '0' + (number % 10);
            print(digit, color);
        }
    }

    void Screen::newLine()
    {
        incYPos();
        xPos = 0;
    }

    void Screen::tab()
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

    void Screen::incXPos()
    {
        if (++xPos > screenWidth) {
            xPos = 0;
            incYPos();
        }
    }

    void Screen::incYPos()
    {
        if(yPos < screenHigh) {
            ++yPos;
        } else {
            scroll(SCROLL_LINES);
        }
    }
