#pragma once

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

namespace Screen {

#define SCREEN_HIGH 25
#define SCREEN_WIDTH 80
#define VIDEO_MEMORY 0xb8000
#define SCROLL_LINES 4

void print(const char *string, int color = color::white);

void print(char *string, int color = color::white);

void print(int number, int color = color::white);

void print(const char symbol, int color = color::white);

void scroll(int lines = 1);

void newLine();

} // namespace Screen
