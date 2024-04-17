#pragma once

#include "chip8state.h"


Chip8State::Chip8State(array<uint8_t, 4096> mem, uint64_t program_size) {
    PC = 0;
    memory = mem;
}