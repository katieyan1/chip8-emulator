
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
        case 0x0:
            switch(addr) {
                case 0x0E0:
                    printf("00E0 - CLS: clear display for %03x\n", addr);
                    break;
                case 0x0EE:
                    printf("00EE\n");
                    state.PC = state.memory[state.SP];
                    state.SP--;
                    break;
                default:
                // default: // note: ignored in omdern interpreters
                //     printf("0nnn - SYS addr: jump to %03x\n", addr);
                //     state.PC = addr;
            }
            break;
        case 0x1:
            printf("1nnn\n");
            state.PC = addr;
            break;
        case 0x2:
            printf("2nnn\n");
            state.SP++;
            state.memory[state.SP] = state.PC;
            state.PC = addr;
            break;
        case 0x3:
            printf("3xkk\n");
            if (state.registers[x] == kk)
                state.PC += 2;
            break;
        case 0x4:
            printf("4xkk\n");
            if (state.registers[x] != kk)
                state.PC += 2;
            break;
        case 0x5:
            printf("5xy0\n");
            if (state.registers[x] == state.registers[y])
                state.PC += 2;
            break;
        case 0x6:
            printf("6xkk\n");
            state.registers[x] = kk;
            break;
        case 0x7:
            printf("7xkk\n");
            state.registers[x] = state.registers[x] + kk;
            break;
        case 0x8:
            switch (nibble) {
                case 0:
                    printf("8xy0\n");
                    state.registers[x] = state.registers[y];
                    break;
                case 1:
                    printf("8xy1\n");
                    state.registers[x] = state.registers[x] | state.registers[y];
                    break;
                case 2:
                    printf("8xy2\n");
                    state.registers[x] = state.registers[x] & state.registers[y];
                    break;
                case 3:
                    printf("8xy3\n");
                    state.registers[x] = state.registers[x] ^ state.registers[y];
                    break;
                case 4:
                    printf("8xy4\n");
                    uint16_t temp = (uint16_t)state.registers[x] + (uint16_t)state.registers[y];
                    state.registers[x] = temp; // lower 8 bits
                    state.VF = temp & 0x0100; // carry bit
                    break;
                case 5:
                    printf("8xy5\n");
                    state.VF = state.registers[x] > state.registers[y] ? 1 : 0;
                    state.registers[x] = state.registers[x] - state.registers[y];
                    break;
                case 6:
                    printf("8xy6\n");
                    state.VF = 0x1 & state.registers[x];
                    state.registers[x] = state.registers[x] >> 1;
                    break;
                case 7:
                    printf("8xy7\n");
                    // TODO come up with enums for VF
                    if (state.registers[y] > state.registers[x])
                    {
                        state.VF = 1;
                    } else {
                        state.VF = 0;
                    }
                    state.registers[x] = state.registers[y] - state.registers[x];
                    break;
                case 0xE:
                    printf("8xyE\n");
                    if (state.registers[x] / 256 != 0)
                    {
                        state.VF = 1;
                    }
                    else
                    {
                        state.VF = 0;
                    }
                    state.registers[x] *= 2;
                    break;
                default:
                    printf("no ins found for 0x8, nibble: %01x\n", nibble);    
            }
            break;
        case 9:
            printf("9xy0\n");
            if(state.registers[x] != state.registers[y]) {
                state.PC += 2;
            }
            break;
        case 0xA:
            printf("Annn\n");
            state.I = addr;
            break;
        case 0xB:
            printf("Bnnn\n");
            state.PC = addr + state.registers[0] - 2;
            break;
        case 0xC:
            printf("Cxkk\n");
            state.registers[x] = rand() & kk;
            break;
        case 0xD:
            // TODO 1 indicates collision, need collision
            printf("Dxyn\n");
            state.VF = 1;
            break;
        case 0xE:
            switch(kk) {
                // TODO assumes one key is pressed at a time
                case 0x9E:
                    printf("Ex9E\n");
                    if(state.K == state.registers[x]) {
                        state.PC += 2;
                    }
                    break;
                case 0xA1:
                    printf("ExA1\n");
                    if(state.K != state.registers[x]) {
                        state.PC += 2;
                    }
                    break;
            }
            break;
        // 8 of these
        case 0xF:
            switch(kk){
                case 0x0A:
                    printf("Fx0A\n");
                    state.registers[x] = state.K;
                    break;
                case 0x15:
                    printf("Fx15\n");
                    //TODO change to state.delaytimer
                    uint8_t DT = state.registers[x];
                    break;
                case 0x18:
                    printf("Fx18\n");
                    //TODO change to state.soundtimer
                    uint8_t ST = state.registers[x];
                    break;
                case 0x1E:
                    printf("Fx1E\n");
                    state.I = state.I + state.registers[x];
                    break;
                case 0x29:
                    printf("Fx29\n");
                    //TODO display instruction
                    state.I = state.registers[x];
                    break;
                case 0x33:
                    printf("Fx33\n");
                    //TODO not sure this is right
                    uint8_t Vx = state.registers[x];
                    state.memory[state.I] = Vx/100;
                    state.memory[state.I+1] = Vx/10 % 10;
                    state.memory[state.I+2] = Vx % 100;
                    break;
                case 0x55:
                    printf("Fx55\n");
                    for (int i = 0; i < x; i++) {
                        state.memory[state.I + i] = state.registers[i];
                    }
                    break;

                case 0x65:
                    printf("Fx65\n");
                    for (int i = 0; i < x; i++) {
                        state.registers[i] = state.memory[state.I + i];
                    }
                    break;

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
