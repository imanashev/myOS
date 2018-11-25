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
        const char tab[] = "    ";
        print(tab);
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

void testCase1()
{
    Screen screen;
    char string1[] = "Hello, C world!\n";
    char string2[] = "FooBar\n";

    screen.print(string1, color::red);
    screen.print(string2, color::green);
    screen.scroll();
}

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

/******************************************/

void main()
{
    testCase2();
}