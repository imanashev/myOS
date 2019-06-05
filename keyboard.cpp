// #include "keyboard.h"
// #include "types.h"
// #include "print.h"
// #include "ports.h"
// #include "isr.h"

// const char *scancodes[] = {
//     "ERROR", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "+", "Backspace", 
//     "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "ENTER", 
//     "LCtrl", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
//     "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/", "Rshift", 
//     "Keypad *", "LAlt", "Spc"
// };

// void print_letter(u8 scancode)
// {
//     /* 'keuyp' event corresponds to the 'keydown' + 0x80 
//      * it may still be a scancode we haven't implemented yet, or
//      * maybe a control/escape sequence */
//     if (scancode <= 0x39) {
//         Screen::print(scancodes[scancode]);

//     } else if (scancode <= 0x7f) {
//         Screen::print("Unknown key down");

//     } else if (scancode <= 0x39 + 0x80) {
//         Screen::print("key up ");
//         print_letter(scancode - 0x80);

//     } else {
//         Screen::print("Unknown key up");
//     }
// }

// void keyboard_callback(registers_t regs)
// {
//     // PIC store scancode in port 0x60
//     u8 scancode = read_byte_from_port(0x60);
//     // Screen::print("Keyboard scancode: ");
//     // Screen::print(scancode);
//     // Screen::print(", ");
//     // print_letter(scancode);
//     // Screen::newLine();
//     Screen::print(1);
// }

// void init_keyboard()
// {
//     register_interrupt_handler(IRQ1, keyboard_callback);

//     char imr;
//     imr = read_byte_from_port(0x21);
//     imr = imr & (0xff - 2); // enable keyboard interrupt (pin 1)
//     send_byte_to_port(0x21, imr);

//     // unsigned char current_data = read_byte_from_port(0x21);
//     // unsigned char clear_bit = current_data & ~(1 << IRQ1);
//     // send_byte_to_port(0x21, clear_bit);
// }

