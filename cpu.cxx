
#include "chip8state.h"
#include "elf.h"
#include "globals.h"
#include "cpu.h"

Chip8State state = Chip8State();

void decode(uint16_t instruction) {
    // cout << "ins: " << setw(4) << setfill('0') << hex << instruction << endl;
    printf("\ninstruction: %04x\n", instruction);

    uint8_t op = (instruction & 0xF000) >> 12;
    printf("op: %01x\n", op);

    uint16_t addr = instruction & ((1 << 12) - 1);
    printf("addr: %03x\n", addr);
    // cout << "addr: " << addr << endl;

    uint8_t nibble = instruction & 0xF;
    printf("nibble: %01x\n", nibble);

    uint8_t x = (instruction & 0x0F00) >> 8;
    printf("x: %01x\n", x);

    // cout << "x: " << x << endl;

    uint8_t y = (instruction & 0x00F0) >> 4;
    printf("y: %01x\n", y);
    // cout << "y: " << y << endl;

    uint8_t kk = instruction & 0xFF;
    printf("kk: %02x\n", kk);
    // cout << "kk: " << kk << endl;

}

void fetch() {
    while (state.PC < (state.program_size))
    {
        uint8_t *code = &state.memory[state.PC];
        printf("%04x %02x %02x", state.PC, code[0], code[1]);

        uint16_t instruction = (code[1] << 8) | code[0];

        decode(instruction);

        state.PC += 2;    
        printf ("\n");    
    }    
}

int main(int argc, char**argv) {
    load_rom(argc, argv);

    fetch();
    
    return 0;
}
