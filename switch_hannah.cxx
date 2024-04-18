#include "cpu.h"
#include "elf.h"
#include "chip8state.h"
#include "globals.h"

void decode_hannah(uint16_t instruction) {
    printf("\ninstruction: %04x\n", instruction);

    uint8_t op = (instruction & 0xF000) >> 12;
    printf("op: %01x\n", op);

    uint16_t addr = instruction & ((1 << 12) - 1);
    printf("addr: %03x\n", addr);

    uint8_t nibble = instruction & 0xF;
    printf("nibble: %01x\n", nibble);

    uint8_t x = (instruction & 0x0F00) >> 8;
    printf("x: %01x\n", x);

    uint8_t y = (instruction & 0x00F0) >> 4;
    printf("y: %01x\n", y);

    uint8_t kk = instruction & 0xFF;
    printf("kk: %02x\n", kk);

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
                // case 7:
                //     printf("8xy7\n");
                //     state.VF = state.registers[y] > state.registers[x] ? 1 : 0;
                //     state.registers[x] = state.registers[y] - state.registers[x];
                //     break;
                // case 0xE:
                //     printf("8xyE\n");
                //     state.VF = state.registers[x] >> 7;
                //     state.registers[x] = state.registers[x] << 1;
                //     break;
                default:
                    printf("no ins found for 0x8, nibble: %01x\n", nibble);    
            }
            break;
        default:
            printf("no decode found.\n");
    }
    
}