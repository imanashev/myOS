#include "keyboard.h"
#include "types.h"
#include "print.h"
#include "ports.h"
#include "isr.h"

const char *scancodes[] = {
    "[ERROR]", "[ESC]", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "+", "[Backspace]",
    "[Tab]", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "[ENTER]",
    "[LCtrl]", "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`",
    "[LShift]", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/", "[Rshift]",
    "[Keypad *]", "[LAlt]", " "
};

const char *parse_code(u8 scancode)
{
    if (scancode <= 0x39) {
        // key down
        return "";

    } else if (scancode <= 0x7f) {
        return "[UnknownKeyDown]";

    } else if (scancode <= 0x39 + 0x80) {
        // key up
        return scancodes[scancode - 0x80];
    } else {
        return "[UnknownKeyUp]";
    }
}

void keyboard_callback(registers_t regs)
{
    // PIC store scancode in port 0x60
    u8 scancode = read_byte_from_port(0x60);
    Screen::print(parse_code(scancode));
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}