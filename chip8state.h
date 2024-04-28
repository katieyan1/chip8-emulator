#pragma once
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <sys/mman.h>
#include <sys/stat.h>
#include <array>
#include <iostream>
#include <iomanip>
#include "globals.h"
#include "display.h"
#include "input.h"

using std::array;
using std::cout;
using std::endl;
using std::hex;
using std::setw;
using std::setfill;

class Chip8State {
    public:
        array<uint8_t, 16> registers;
        uint16_t I;
        uint16_t SP;
        uint16_t PC;
        uint64_t program_size;
        array<uint16_t, 16> stack;
        array<uint8_t, MEMORY_SIZE> memory;
        Input key_states;
        uint8_t VF;
        uint8_t DT;
        uint8_t ST;
        array<uint32_t, WIDTH*HEIGHT> display_array;
        bool draw_flag;

        Chip8State();
        Chip8State(array<uint8_t, MEMORY_SIZE> mem, uint64_t program_size);
        void set_memory(array<uint8_t, MEMORY_SIZE> mem);
        void set_program_size(uint64_t program_size);
        void draw(uint32_t opcode);
};
