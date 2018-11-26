#define SCREEN_HIGH 25
#define SCREEN_WIDTH 80
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
    Screen() : screenHigh(SCREEN_HIGH),
               screenWidth(SCREEN_WIDTH),
               videoMemory((unsigned short *)0xb8000),
               xPos(0),
               yPos(0)
    {}

    void print(const char *string, int color = color::white) {
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

    void print(int number, int color = color::white) {
        // Todo: cant print 0
        if(number != 0) {
            print(number / 10, color);
            const char digit = '0' + (number % 10);
            print(digit, color);
        }
    }

    void print(const char symbol, int color = color::white) {
        videoMemory[yPos * screenWidth + xPos] = symbol | (color << 8);
        incXPos();
    }

    void scroll(int lines = 1) {
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

private:
    void newLine() {
        incYPos();
        xPos = 0;
    }

    void tab() {
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

    void incXPos() {
        if (++xPos > screenWidth) {
            xPos = 0;
            incYPos();
        }
    }

    void incYPos() {
        if(yPos < screenHigh) {
            ++yPos;
        } else {
            scroll(SCROLL_LINES);
        }
    }

    int xPos;
    int yPos;

    const int screenHigh;
    const int screenWidth;

    unsigned short *videoMemory;
};

/******************************************/

// scroll 1
void testCase1()
{
    Screen screen;

    screen.print("Hello, C world!\n", color::red);
    screen.print("FooBar\n", color::green);
    screen.scroll();
}

// scroll 2
void testCase2()
{
    Screen screen;
    char string[] = ":\tHello, C world!\n";
    int i = 1;
    while(i <= 20) {
        screen.print(i);
        screen.print(string, i % 15 + 1);
        ++i;
    }
    int j = 0;
    while(true) {
        if(j % 10000000 == 0) {
            screen.print(i);
            screen.print(string, i % 15 + 1);
            ++i;
        }
        ++j;
    }
}

// tabs
void testCase3()
{
    Screen screen;

    screen.print("12341234123412341234123412341234123412341234123412341234123412341234123412341234\n");
    screen.print("\ttab\n");
    screen.print("1\ttab\n");
    screen.print("12\ttab\n");
    screen.print("123\ttab\n");
    screen.print("1234\ttab\n");
    screen.print("23456789abcdefghijklmnopqrstuvwxyz123456789123456789abcdefghijklmnopqrstuvwxyz\t12");
}

/******************************************/

void main()
{
    testCase3();
}