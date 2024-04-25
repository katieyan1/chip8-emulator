#include "chip8state.h"


Chip8State::Chip8State(array<uint8_t, MEMORY_SIZE> mem, uint64_t size) {
    PC = 0;
    SP = 0;
    DT = 0;
    ST = 0;
    memory = mem;
    program_size = size;
    display_array.fill(0);
    draw_flag = false;
    stack.fill(0);
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





void Chip8State::draw(uint32_t opcode) {
    registers[0xF] = 0;
    uint16_t x = registers[((opcode & 0x0f00) >> 8)];
    uint16_t y = registers[((opcode & 0x00f0) >> 4)];
    uint16_t height = registers[(opcode & 0x000f)];

    
    for (uint16_t row = 0; row < height; row++) {
        uint8_t line = memory[I + row]; 
        for (uint8_t col = 0; col < 8; col++) {
            // check from left to right if 'line' position is on/off
            if (line & (0x10000000 >> col)) {
                // calculate display array index
                uint32_t pixel_index = (((y+row) % HEIGHT) * WIDTH) + ((x+col) % WIDTH);
                if (display_array[pixel_index] == 1) {
                    registers[0xF] = 1;
                }
                display_array[pixel_index] ^= 1;

                // uint32_t pixel = display_array[pixel_index];

                // set_pixel((y+row) % HEIGHT, (x+col) % WIDTH, pixel);
                // set_pixel((uint16_t) ((y+row) % HEIGHT), (uint16_t) ((x+col) % WIDTH), (uint32_t) display[pixel_index]);
                // void SetPixel(int x, int y, Uint32 pixel)
            }
        }
    }
    draw_flag = true;

}