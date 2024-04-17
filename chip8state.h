#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <sys/mman.h>
#include <sys/stat.h>
#include <array>
using std::array;

class Chip8State {
    public:
        array<uint8_t, 16> registers;
        uint16_t I;
        uint16_t SP;
        uint16_t PC;
        uint64_t program_size;
        array<uint8_t, 4096> memory;
        Chip8State(array<uint8_t, 4096> mem, uint64_t program_size);
};

