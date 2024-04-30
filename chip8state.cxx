#include "chip8state.h"


Chip8State::Chip8State(array<uint8_t, MEMORY_SIZE> mem, uint64_t size) {
    PC = 0x200;
    SP = 0;
    DT = 0;
    ST = 0;
    I = 0;
    memory = mem;
    program_size = size;
    display_array.fill(0);
    draw_flag = false;
    stack.fill(0);
    registers.fill(0);

    for (int i = 0; i < 80; ++i) {
        memory[i] = FONTS[i];
    }
    key_states = Input();
}

Chip8State::Chip8State() {
    PC = 0;
    SP = 0;
    DT = 0;
    ST = 0;
    display_array.fill(255);
    draw_flag = false;
    stack.fill(0);
}

void Chip8State::set_memory(array<uint8_t, MEMORY_SIZE> mem) {
    memory = mem;
}

void Chip8State::set_program_size(uint64_t input_program_size) {
    program_size = input_program_size;
}