#pragma once

// panic
void testCase1();

// colored print and scroll
void testCase2();

// tabs
void testCase3();

// interrupts without error code
void testCase4();

// interrupt with error code (endless loop because stack is corrupted)
void testCase5();

// timer through pic8259 (works only in debug mode. Don't forget to change TICKS_FOR_PRINT in timer.h)
void testCase6();

// keyboard through pic8259
void testCase7();

// multitasking
void testCase8();
