#include "rom.h"

#include <iostream>
#include <unordered_map>
using namespace std;

class Rom {
    public:
        unordered_map<uint64_t, uint8_t> memory;
        void mem_write8(uint64_t addr, uint8_t data);
};

void Rom::mem_write8(uint64_t addr, uint8_t data) {
    memory[addr] = data;
}