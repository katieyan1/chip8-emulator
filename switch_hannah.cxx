// #include "cpu.h"
// #include "elf.h"
// #include "chip8state.h"

// void decode_hannah(uint16_t instruction) {
//     // cout << "ins: " << setw(4) << setfill('0') << hex << instruction << endl;
//     printf("\ninstruction: %04x\n", instruction);

//     uint8_t op = (instruction & 0xF000) >> 12;
//     printf("op: %01x\n", op);

//     uint16_t addr = instruction & ((1 << 12) - 1);
//     printf("addr: %03x\n", addr);
//     // cout << "addr: " << addr << endl;

//     uint8_t nibble = instruction & 0xF;
//     printf("nibble: %01x\n", nibble);

//     uint8_t x = (instruction & 0x0F00) >> 8;
//     printf("x: %01x\n", x);

//     // cout << "x: " << x << endl;

//     uint8_t y = (instruction & 0x00F0) >> 4;
//     printf("y: %01x\n", y);
//     // cout << "y: " << y << endl;

//     uint8_t kk = instruction & 0xFF;
//     printf("kk: %02x\n", kk);
//     // cout << "kk: " << kk << endl;

//     switch(op) {
//         case 0x0:
//             printf("0nnn SYS addr: jump to %03x\n", addr);
//             break;

//         default:
//             printf("no decode found.\n");
//     }
    
// }