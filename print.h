#pragma once

#define SCREEN_HIGH 25
#define SCREEN_WIDTH 80
#define VIDEO_MEMORY 0xb8000
#define SCROLL_LINES 4

namespace color {
    enum {
        black,        blue,
        green,        cyan,
        red,          magenta,
        brown,        light_gray,
        dark_gray,    light_blue,
        light_green,  light_cyan,
        light_red,    light_magenta,
        yellow,       white
    };
} // namespace color

class Screen {
public:
    Screen();

    void print(const char *string, int color = color::white);

    void print(int number, int color = color::white);

    void print(const char symbol, int color = color::white);

    void scroll(int lines = 1);

private:
    void printNumHelper(int number, int color = color::white);

    void newLine();

    void tab();

    void incXPos();

    void incYPos();

    int xPos;
    int yPos;

    const int screenHigh;
    const int screenWidth;

    unsigned short *videoMemory;
};
