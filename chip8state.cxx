#include "chip8state.h"

Chip8State::Chip8State(array<uint8_t, 4096> mem, uint64_t size) {
    PC = 0;
    memory = mem;
    program_size = size;
}

Chip8State::Chip8State() {
    PC = 0;
}

void Chip8State::set_memory(array<uint8_t, 4096> mem) {
    memory = mem;
}

void Chip8State::set_program_size(uint64_t program_size) {
    program_size = program_size;
}