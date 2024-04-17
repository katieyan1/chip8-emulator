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
        array<uint8_t, 4096> memory;
        Chip8State();
        Chip8State(array<uint8_t, 4096> mem, uint64_t program_size);
        void set_memory(array<uint8_t, 4096> mem);
        void set_program_size(uint64_t program_size);
};
