#include "chip8state.h"
#include "elf.h"

int main(int argc, char**argv) {
    Chip8State state = load_rom(argc, argv);
    while (state.PC < (state.program_size))
    {
        uint8_t *code = &state.memory[state.PC];
        printf("%04x %02x %02x", state.PC, code[0], code[1]);
        state.PC += 2;    
        printf ("\n");    
    }    
    return 0;
}
