#include "cpu.h"

Chip8State state;

/* DEBUGGING*/
bool debug = false;

void decode(uint16_t instruction) {

    uint8_t op = (instruction & 0xF000) >> 12;
    uint16_t addr = instruction & ((1 << 12) - 1);
    uint8_t nibble = instruction & 0xF;
    uint8_t x = (instruction & 0x0F00) >> 8;
    uint8_t y = (instruction & 0x00F0) >> 4;
    uint8_t kk = instruction & 0xFF;

    if (debug) {
        printf("\ninstruction: %04x\n", instruction);
        printf("op: %01x\n", op);
        printf("addr: %03x\n", addr);
        printf("nibble: %01x\n", nibble);
        printf("x: %01x\n", x);
        printf("y: %01x\n", y);
        printf("kk: %02x\n", kk);
    }
    
    switch(op) {
        case 0x0: {
            switch(addr) {
                case 0x0E0: {
                    if (debug) printf("00E0 - CLS: clear display for %03x\n", addr);
                    state.display_array.fill(0);
                    state.draw_flag = true;
                    break;
                }
                case 0x0EE: {
                    if (debug) printf("00EE\n"); // RET - return from subroutine
                    state.SP--;
                    state.PC = state.stack[state.SP];
                    break;
                }
            }
            break;
        }
        case 0x1:{
            if (debug) printf("1nnn\n"); // JP addr
            state.PC = addr - 2;
            break;
        }
        case 0x2:{
            if (debug) printf("2nnn\n"); // CALL addr
            state.stack[state.SP] = state.PC;
            state.SP++;
            state.PC = addr - 2;
            break;
        }
        case 0x3:{
            if (debug) printf("3xkk\n"); // SKIP next ins
            if (state.registers[x] == kk)
                state.PC += 2;
            break;
        }
        case 0x4:{
            if (debug) printf("4xkk\n"); // SKIP next ins
            if (state.registers[x] != kk)
                state.PC += 2;
            break;
        }
        case 0x5:{
            if (debug) printf("5xy0\n"); // SKIP next ins
            if (state.registers[x] == state.registers[y])
                state.PC += 2;
            break;
        }
        case 0x6:{ 
            if (debug) printf("6xkk\n"); // LD Vx, byte
            state.registers[x] = kk;
            break;
        }
        case 0x7:{
            if (debug) printf("7xkk\n"); // ADD Vx, byte
            state.registers[x] = state.registers[x] + kk;
            break;
        }
        case 0x8: {
            switch (nibble) {
                case 0:{
                    if (debug) printf("8xy0\n"); // LD Vx, Vy
                    state.registers[x] = state.registers[y];
                    break;
                }
                case 1:{
                    if (debug) printf("8xy1\n"); // OR Vx, Vy
                    state.registers[x] = state.registers[x] | state.registers[y];
                    break;
                }
                case 2:{
                    if (debug) printf("8xy2\n"); // AND Vx, Vy
                    state.registers[x] = state.registers[x] & state.registers[y];
                    break;
                }
                case 3:{
                    if (debug) printf("8xy3\n"); // XOR Vx, Vy
                    state.registers[x] = state.registers[x] ^ state.registers[y];
                    break;
                } 
                case 4:{
                    if (debug) printf("8xy4\n"); // ADD Vx, Vy
                    uint16_t temp = (uint16_t)state.registers[x] + (uint16_t)state.registers[y];
                    state.registers[x] = temp; // lower 8 bits
                    state.registers[0xF] = temp > 0x0FF ? 1 : 0; // carry bit
                    break;
                }
                case 5:{
                    if (debug) printf("8xy5\n"); // SUB Vx, Vy
                    state.registers[0xF] = state.registers[x] >= state.registers[y] ? 1 : 0;
                    state.registers[x] = state.registers[x] - state.registers[y];
                    break;
                }
                case 6:{
                    if (debug) printf("8xy6\n"); // SHR Vx {, Vy}
                    state.registers[0xF] = 0x1 & state.registers[x];
                    state.registers[x] = state.registers[x] >> 1;
                    break;
                }
                case 7:{
                    if (debug) printf("8xy7\n"); // SUBN Vx, Vy
                    state.registers[0xF] = state.registers[y] >= state.registers[x] ? 1 : 0;
                    state.registers[x] = state.registers[y] - state.registers[x];
                    break;
                }
                case 0xE:{
                    if (debug) printf("8xyE\n"); // SHL Vx {, Vy}
                    state.registers[0xF] = state.registers[x] / 256 != 0 ? 1 : 0;
                    state.registers[x] *= 2;
                    break;
                    // default:
                    //     printf("no ins found for 0x8, nibble: %01x\n", nibble);
                }
            }
            break;
        }
        case 9:{
            if (debug) printf("9xy0\n"); // SNE Vx, Vy
            if(state.registers[x] != state.registers[y]) {
                state.PC += 2;
            }
            break;
        }
        case 0xA:{
            if (debug) printf("Annn\n"); // LD I, addr
            state.I = addr;
            break;
        }
        case 0xB:{
            if (debug) printf("Bnnn\n"); // JP V0, addr
            state.PC = addr + state.registers[0] -2;
            break;
        }
        case 0xC:{
            if (debug) printf("Cxkk\n"); // RND Vx, byte
            state.registers[x] = rand() & kk;
            break;
        }
        case 0xD:{
            if (debug) {
                printf("Dxyn\n");
            }
            state.registers[0xF] = 0;
            uint8_t pixel;
            uint8_t Vx = state.registers[x];
            uint8_t Vy = state.registers[y];
            for (int yline = 0; yline < nibble; yline++) { // get each line of bits
                pixel = state.memory[state.I + yline];
                for(int xline = 0; xline < 8; xline++) { // get each bit
                    if (debug) printf("this is xline %d and yline %d and pixel %d\n", xline, yline, (pixel & (0x80 >> xline)));
                    if((pixel & (0x80 >> xline)) != 0) {
                        uint64_t pixel_index = ((Vx + xline) % WIDTH + (((Vy + yline) % HEIGHT) * 64));
                        
                        // 'switch' pixel on or off
                        if (state.display_array[pixel_index] == 1)
                        {
                            state.registers[0xF] = 1;
                        }
                        state.display_array[pixel_index] ^= 1;
                    }
                }

            }
            state.draw_flag = true;
            break;
        }
        case 0xE: {
            switch(kk) { 
                case 0x9E:{
                    if (debug) printf("Ex9E\n"); // SKP Vx
                    if(state.key_states.keys[state.registers[x]] == 1) {
                        state.PC += 2;
                    }
                    break;
                }
                case 0xA1:{
                    if (debug) printf("ExA1\n"); // SKNP Vx
                    if(state.key_states.keys[state.registers[x]] == 0) {
                        state.PC += 2;
                    }
                    break;
                }
            }
            break;
        }
        // 8 of these
        case 0xF: {
            switch(kk){
                case 0x7:{
                    if (debug) printf("Fx07\n"); // LD Vx, DT
                    state.registers[x] = state.DT;
                    break;
                }
                case 0x0A:{
                    if (debug) printf("Fx0A\n"); // LD Vx, K
                    bool key_pressed = false;
                    for (int i = 0; i < 16; i++)
                    {
                        if(state.key_states.keys[i] == 1) {
                            key_pressed = true;
                            state.registers[x] = i;
                            if (debug) printf("key pressed at: %02x", i);
                            break;
                        }
                    }
                    if(!key_pressed) {
                        state.PC -= 2;
                    }
                    break;
                }
                case 0x15:{
                    if (debug) printf("Fx15\n"); // LD DT, Vx
                    state.DT = state.registers[x];
                    break;
                }
                case 0x18:{
                    if (debug) printf("Fx18\n"); // LD ST, Vx
                    state.ST = state.registers[x];
                    break;
                }
                case 0x1E:{
                    if (debug) printf("Fx1E\n"); // ADD I, Vx
                    state.I + state.registers[x] > 0xFFF ? state.registers[0xF] = 1 : state.registers[0xF] = 0;
                    state.I += state.registers[x];
                    state.I &= 0xFFF;
                    break;
                }
                case 0x29:{
                    if (debug) printf("Fx29\n"); // LD F, Vx
                    state.I = state.registers[x]*5;
                    state.I &= 0xFFF;
                    break;
                }
                case 0x33:{
                    if (debug) printf("Fx33\n"); // LD B, Vx Store hundreds digit, tens digit, ones digit of Vx in memory locations I, I+1, and I+2.
                    uint8_t Vx = state.registers[x];
                    state.memory[state.I] = Vx/100;
                    state.memory[state.I+1] = (Vx/10) % 10;
                    state.memory[state.I+2] = Vx % 100;
                    break;
                }
                case 0x55:{
                    if (debug) printf("Fx55\n"); // LD [I], Vx Store registers V0 through Vx in memory starting at location I.
                    for (int i = 0; i < x; i++) {
                        state.memory[state.I + i] = state.registers[i];
                    }
                    break;
                }
                case 0x65:{
                    if (debug) printf("Fx65\n"); // LD Vx, [I], Read registers V0 through Vx from memory starting at location I.
                    for (int i = 0; i < x; i++) {
                        state.registers[i] = state.memory[state.I + i];
                    }
                    break;
                }
            }
            break;
        }
        default: {
            cout << "nothing found?!" << endl;
        }
    }

    if (state.DT > 0) // decrement delay timer
        --state.DT;

    if (state.ST > 0) // decrement sound timer
        --state.ST;
}

uint16_t fetch() {
    uint8_t *code = &state.memory[state.PC];
    if (debug) printf("%04x %02x %02x\n", state.PC, code[0], code[1]);

    // big endian
    uint16_t instruction = (code[0] << 8) | code[1];

    return instruction;

}

int main(int argc, char**argv) {
    state = load_rom(argc, argv);

    Display SDL_display = Display(argv[1]);

    SDL_Event window_event;

    state.PC = 0x200;
    array<uint32_t, WIDTH * HEIGHT> display_arr_new = state.display_array;
    while (state.PC < 4096)
    {
        uint16_t ins = fetch();        
        decode(ins);

        /* CHECK FOR KEYBOARD INPUT */
        while(SDL_PollEvent(&window_event)) {
            if (window_event.type == SDL_QUIT) exit(0);
            else if(window_event.type == SDL_KEYDOWN) {
                for (int i = 0; i < 16; ++i) {
                    if (window_event.key.keysym.sym == KEYMAP[i]) {
                        state.key_states.keys[i] = 1;
                    }
                }
            }
            else if(window_event.type == SDL_KEYUP) {
                for (int i = 0; i < 16; ++i) {
                    if (window_event.key.keysym.sym == KEYMAP[i]) {
                        state.key_states.keys[i] = 0;
                    }
                }
            }            

        }

        /* UPDATE GUI */
        if (state.draw_flag){
            state.draw_flag = false;
            if (debug) cout << "DRAWING" << endl;
            display_arr_new = SDL_display.render(state.display_array);
        }

        sleep_for(std::chrono::microseconds(1200));

        /* INCREMENT PC */
        state.PC += 2; 

    }    

    return 0;
}
