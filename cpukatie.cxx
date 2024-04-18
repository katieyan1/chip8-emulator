
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

    switch(op) {
        case 8:
            switch(nibble){
                case 0x6:
                    printf("8xyE");
                    if (state.registers[x] % 2 != 0)
                    {
                        state.VF = 1;
                    }
                    else
                    {
                        state.VF = 0;
                    }
                    state.registers[x] *= 2;
                case 7:
                    printf("8xy7");
                    // TODO come up with enums for VF
                    if (state.registers[y] > state.registers[x])
                    {
                        state.VF = 1;
                    } else {
                        state.VF = 0;
                    }
                    state.registers[x] = state.registers[y] - state.registers[x];

                case 0xE:
                    printf("8xyE");
                    if (state.registers[x] / 256 != 0)
                    {
                        state.VF = 1;
                    }
                    else
                    {
                        state.VF = 0;
                    }
                    state.registers[x] *= 2;
                }
        case 9:
            printf("9xy0");
            if(state.registers[x] != state.registers[y]) {
                state.PC += 2;
            }
        case 0xA:
            printf("Annn");
            state.I = addr;
        case 0xB:
            printf("Bnnn");
            state.PC = addr + state.registers[0] - 2;
        case 0xC:
            printf("Cxkk");
            state.registers[x] = rand() & kk;
        case 0xD:
            // TODO 1 indicates collision, need collision
            printf("Dxyn");
            state.VF = 1;
        case 0xE:
            switch(kk) {
                // TODO assumes one key is pressed at a time
                case 0x9E:
                    printf("Ex9E");
                    if(state.K == state.registers[x]) {
                        state.PC += 2;
                    }
                case 0xA1:
                    printf("ExA1");
                    if(state.K != state.registers[x]) {
                        state.PC += 2;
                    }                
            }
        // 8 of these
        case 0xF:
            switch(kk){
                case 0x0A:
                    printf("Fx0A");
                    state.registers[x] = state.K;
                case 0x15:
                    printf("Fx15");
                    //TODO change to state.delaytimer
                    uint8_t DT = state.registers[x];
                case 0x18:
                    printf("Fx18");
                    //TODO change to state.soundtimer
                    uint8_t ST = state.registers[x];
                case 0x1E:
                    printf("Fx1E");
                    state.I = state.I + state.registers[x];
                case 0x29:
                    printf("Fx29");
                    //TODO display instruction
                    state.I = state.registers[x];
                case 0x33:
                    printf("Fx33");
                    //TODO not sure this is right
                    uint8_t Vx = state.registers[x];
                    state.memory[state.I] = Vx/100;
                    state.memory[state.I+1] = Vx/10 % 10;
                    state.memory[state.I+2] = Vx % 100;
                case 0x55:
                    printf("Fx55");
                    for (int i = 0; i < x; i++) {
                        state.memory[state.I + i] = state.registers[i];
                    }
                case 0x65:
                    printf("Fx65");
                    for (int i = 0; i < x; i++) {
                        state.registers[i] = state.memory[state.I + i];
                    }
                }
    }
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
