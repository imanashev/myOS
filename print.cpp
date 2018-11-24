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
        while(currentPosition <= screenHigh * screenWidth) {
            *newHeadAddress++ = 0;
            ++currentPosition;
        }

        // if(yPosition - lines >= 0) {
        //     yPosition -= lines;
        // } else {
        //     yPosition = 0;
        // }
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
            scroll();
            yPosition -=1;
        }
    }

    unsigned short *startAddress; // const
    unsigned short *headAddress;

    int xPosition;
    int yPosition;

    int screenHigh;  // const
    int screenWidth;  // const
};

void main()
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