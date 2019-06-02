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

    static void print(const char *string, int color = color::white);

    static void print(int number, int color = color::white);

    static void print(const char symbol, int color = color::white);

    static void scroll(int lines = 1);

private:
    static void printNumHelper(int number, int color = color::white);

    static void newLine();

    static void tab();

    static void incXPos();

    static void incYPos();

    static int xPos;
    static int yPos;

    static const int screenHigh = SCREEN_HIGH;
    static const int screenWidth = SCREEN_WIDTH;

    static unsigned short *videoMemory;
};
