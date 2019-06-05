#pragma once
#include "types.h"

void send_byte_to_port(u16 port, u8 data);
u8 read_byte_from_port(u16 port);
