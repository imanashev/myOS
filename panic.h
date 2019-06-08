#define panic(errorMsg) _panic(errorMsg, __FILE__, __LINE__)

#ifndef PANIC_H
#define PANIC_H

void _panic(const char *errorMsg, const char *path, int line);

#endif
