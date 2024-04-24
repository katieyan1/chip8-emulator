#include "chip8state.h"

Chip8State::Chip8State(array<uint8_t, MEMORY_SIZE> mem, uint64_t size) {
    PC = 0;
    SP = 0;
    DT = 0;
    ST = 0;
    memory = mem;
    program_size = size;
}

Chip8State::Chip8State() {
    PC = 0;
    SP = 0;
    DT = 0;
    ST = 0;
}

void Chip8State::set_memory(array<uint8_t, MEMORY_SIZE> mem) {
    memory = mem;
}

void Chip8State::set_program_size(uint64_t program_size) {
    program_size = program_size;
}