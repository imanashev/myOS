#pragma once
#include "types.h"

namespace port {

void outb(u16 port, u8 data);
u8 inb(u16 port);

} // namespace port
