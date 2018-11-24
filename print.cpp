namespace color {

enum {
    black,
    blue,	
    green,
    cyan,	
    red,
    magenta,	
    brown,
    light_gray,
    dark_gray,
    light_blue,	
    light_green,	
    light_cyan,
    light_red,
    light_magenta,	
    yellow,
    white
};

} // namespace color


class Display {
public:
    Display() {
        headAddress = startAddress = (unsigned short*)0xB8000;
        xPosition = yPosition = 0;
        screenHigh = 25;
        screenWidth = 80;
    };

    void print(char *string, int color = color::white) { 
        char *symbol = string;
        while(*symbol != 0) {
            switch (*symbol) {
            case 9: {
                printTab();
                break;
            }
            case 10: {
                newLine();
                break;
            }
            default: {
                print(*symbol, color);
            }
            }
            ++symbol;
        }
    }

    void print(int number, int color = color::white) {
        if(number != 0) {
            print(number / 10, color);
            char digit = '0' + (number % 10);
            print(digit, color);
        }
    }

    void scroll(int lines = 1) {
        int skippedBytes = lines * screenWidth;
        unsigned short *newHeadAddress = startAddress;
        unsigned short *scrolled = startAddress + skippedBytes;

        int currentPosition = skippedBytes;
        while (currentPosition <= yPosition * screenWidth + xPosition) {
            *newHeadAddress++ = *scrolled++;
            ++currentPosition;
        }
        headAddress = --newHeadAddress;
        while(currentPosition <= screenHigh * screenWidth * 2) {
            *newHeadAddress++ = (unsigned short) 0;
            ++currentPosition;
        }

        if(yPosition - (lines - 1) >= 0) {
            yPosition -= (lines -1);
        } else {
            yPosition = 0;
        }
    }

    void print(int xPos, int yPos, char *string, int color = color::white) {
        if ((xPos >= 0 && xPos <= screenWidth) && (yPos >= 0 && yPos <= screenHigh)) {
            xPosition = xPos;
            yPosition = yPos;
            headAddress = startAddress + (yPosition * screenWidth) + xPosition; 
            print(string, color);
        } else {
            char error[] = "\nError: incorrect position";
            print(error, color::red);
        }
    }

private:
    void print(char symbol, int color = color::white) {
        incXPosition();
        *headAddress++ = symbol | (color << 8);
    }

    void newLine() {
        incYPosition();
        int skipSpace = screenWidth - xPosition;
        headAddress = headAddress + skipSpace;
        xPosition = 0;
    }

    void printTab() {
        char tab[] = "    ";
        print(tab);
    }

    void incXPosition() {
        if (++xPosition > screenWidth) {
            xPosition = 0;
            incYPosition();
        }
    }

    void incYPosition() {
        if(++yPosition > screenHigh) {
            --yPosition;
            scroll(6);
        }
    }

    unsigned short *startAddress; // const
    unsigned short *headAddress;

    int xPosition;
    int yPosition;

    int screenHigh;  // const
    int screenWidth;  // const
};

/******************************************/

void testCase1()
{
    Display display;
    char string1[] = "Hello, C world!\n";
    char string2[] = "FooBar\n";

    display.print(string1, color::red);
    display.print(string2, color::green);
    display.scroll();
}

void testCase2() 
{
    Display display;
    char string[] = ": \tHello, C world!\n";
    int i = 0;
    int j = 0;
    while(i < 20) {
        display.print(i);
        display.print(string, i++ %15 + 1);
    }
    while(true) {
        if(j %10000000 == 0) {
            display.print(i);
            display.print(string, i++ %15 + 1);
        }
        j++;
    }
}

void testCase3()
{
    Display display;
    char string[] = "Hello, C world!";

    display.print(string);
    display.print(10, 10, string, color::green);
    display.print(string);
    display.print(10, 100, string);
}
/******************************************/

void main()
{
    testCase3();
}