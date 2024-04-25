#include "cpu.h"

Chip8State state;

void decode(uint16_t instruction) {
    // cout << "ins: " << setw(4) << setfill('0') << hex << instruction << endl;
    printf("\ninstruction: %04x\n", instruction);

    uint8_t op = (instruction & 0xF000) >> 12;
    printf("op: %01x\n", op);

    uint16_t addr = instruction & ((1 << 12) - 1);
    printf("addr: %03x\n", addr);
    // // cout << "addr: " << addr << endl;

    uint8_t nibble = instruction & 0xF;
    printf("nibble: %01x\n", nibble);

    uint8_t x = (instruction & 0x0F00) >> 8;
    printf("x: %01x\n", x);

    // // cout << "x: " << x << endl;

    uint8_t y = (instruction & 0x00F0) >> 4;
    printf("y: %01x\n", y);
    // // cout << "y: " << y << endl;

    uint8_t kk = instruction & 0xFF;
    printf("kk: %02x\n", kk);
    // cout << "kk: " << kk << endl;
    switch(op) {
        case 0x0: {
            switch(addr) {
                case 0x0E0: {
                    printf("00E0 - CLS: clear display for %03x\n", addr);
                    state.display_array.fill(0);
                    state.draw_flag = true;
                    break;
                }
                case 0x0EE: {
                    printf("00EE\n");
                    state.SP--;
                    state.PC = state.stack[state.SP];
                    break;
                }
            }
            break;
        }
        case 0x1:{
            printf("1nnn\n");
            state.PC = addr - 2;
            break;
        }
        case 0x2:{
            printf("2nnn\n");
            state.stack[state.SP] = state.PC;
            state.SP++;
            state.PC = addr - 2;
            break;
        }
        case 0x3:{
            printf("3xkk\n");
            if (state.registers[x] == kk)
                state.PC += 2;
            break;
        }
        case 0x4:{
            printf("4xkk\n");
            if (state.registers[x] != kk)
                state.PC += 2;
            break;
        }
        case 0x5:{
            printf("5xy0\n");
            if (state.registers[x] == state.registers[y])
                state.PC += 2;
            break;
        }
        case 0x6:{
            printf("6xkk\n");
            state.registers[x] = kk;
            break;
        }
        case 0x7:{
            printf("7xkk\n");
            state.registers[x] = state.registers[x] + kk;
            break;
        }
        case 0x8: {
            switch (nibble) {
                case 0:{
                    printf("8xy0\n");
                    state.registers[x] = state.registers[y];
                    break;
                }
                case 1:{
                    printf("8xy1\n");
                    state.registers[x] = state.registers[x] | state.registers[y];
                    break;
                }
                case 2:{
                    printf("8xy2\n");
                    state.registers[x] = state.registers[x] & state.registers[y];
                    break;
                }
                case 3:{
                    printf("8xy3\n");
                    state.registers[x] = state.registers[x] ^ state.registers[y];
                    break;
                } 
                case 4:{
                    printf("8xy4\n");
                    uint16_t temp = (uint16_t)state.registers[x] + (uint16_t)state.registers[y];
                    state.registers[x] = temp; // lower 8 bits
                    state.registers[0xF] = temp > 0x0FF ? 1 : 0; // carry bit
                    break;
                }
                case 5:{
                    printf("8xy5\n");
                    state.registers[0xF] = state.registers[x] > state.registers[y] ? 1 : 0;
                    state.registers[x] = state.registers[x] - state.registers[y];
                    break;
                }
                case 6:{
                    printf("8xy6\n");
                    state.registers[0xF] = 0x1 & state.registers[x];
                    state.registers[x] = state.registers[x] >> 1;
                    break;
                }
                case 7:{
                    printf("8xy7\n");
                    if (state.registers[y] > state.registers[x])
                    {
                        state.registers[0xF] = 1;
                    } else {
                        state.registers[0xF] = 0;
                    }
                    state.registers[x] = state.registers[y] - state.registers[x];
                    break;
                }
                case 0xE:{
                    printf("8xyE\n");
                    if (state.registers[x] / 256 != 0)
                    {
                        state.registers[0xF] = 1;
                    }
                    else
                    {
                        state.registers[0xF] = 0;
                    }
                    state.registers[x] *= 2;
                    break;
                    // default:
                    //     printf("no ins found for 0x8, nibble: %01x\n", nibble);
                }
            }
            break;
        }
        case 9:{
            printf("9xy0\n");
            if(state.registers[x] != state.registers[y]) {
                state.PC += 2;
            }
            break;
        }
        case 0xA:{
            printf("Annn\n");
            state.I = addr;
            break;
        }
        case 0xB:{
            printf("Bnnn\n");
            state.PC = addr + state.registers[0] -2;
            break;
        }
        case 0xC:{
            printf("Cxkk\n");
            state.registers[x] = rand() & kk;
            break;
        }
        case 0xD:{
            // TODO 1 indicates collision, need collision
            printf("Dxyn\n");
            // printf("this is what is in I %d\n", state.I);
            // printf("this is what is in memory at I %d\n", state.memory[state.I + 1]);
            state.registers[0xF] = 0;
            uint8_t pixel;
            uint8_t Vx = state.registers[x];
            uint8_t Vy = state.registers[y];
            for (int yline = 0; yline < nibble; yline++) {
                pixel = state.memory[state.I + yline];
                for(int xline = 0; xline < 8; xline++) {
                    printf("this is xline %d and yline %d and pixel %d\n", xline, yline, (pixel & (0x80 >> xline)));
                    if((pixel & (0x80 >> xline)) != 0) {
                        uint64_t pixel_index = ((Vx + xline) % WIDTH + (((Vy + yline) % HEIGHT) * 64));
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
                // TODO assumes one key is pressed at a time
                case 0x9E:{
                    printf("Ex9E\n");
                    if(state.K == state.registers[x]) {
                        state.PC += 2;
                    }
                    break;
                }
                case 0xA1:{
                    printf("ExA1\n");
                    if(state.K != state.registers[x]) {
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
                    printf("Fx07\n");
                    state.registers[x] = state.DT;
                    break;
                }
                case 0x0A:{
                    printf("Fx0A\n");
                    state.registers[x] = state.K;
                    break;
                }
                case 0x15:{
                    printf("Fx15\n");
                    state.DT = state.registers[x];
                    break;
                }
                case 0x18:{
                    printf("Fx18\n");
                    state.ST = state.registers[x];
                    break;
                }
                case 0x1E:{
                    printf("Fx1E\n");
                    state.I + state.registers[x] > 0xFFF ? state.registers[0xF] = 1 : state.registers[0xF] = 0;
                    state.I += state.registers[x];
                    state.I &= 0xFFF;
                    break;
                }
                case 0x29:{
                    printf("Fx29\n");
                    state.I = state.registers[x]*5;
                    state.I &= 0xFFF;
                    break;
                }
                case 0x33:{
                    printf("Fx33\n");
                    uint8_t Vx = state.registers[x];
                    state.memory[state.I] = Vx/100;
                    state.memory[state.I+1] = (Vx/10) % 10;
                    state.memory[state.I+2] = Vx % 100;
                    break;
                }
                case 0x55:{
                    printf("Fx55\n");
                    for (int i = 0; i < x; i++) {
                        state.memory[state.I + i] = state.registers[i];
                    }
                    break;
                }
                case 0x65:{
                    printf("Fx65\n");
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

    if (state.DT > 0)
        --state.DT;

    if (state.ST > 0)
        if(state.ST == 1);
            // TODO: Implement sound
        --state.ST;
}

uint16_t fetch() {
    uint8_t *code = &state.memory[state.PC];
    printf("%04x %02x %02x\n", state.PC, code[0], code[1]);

    uint16_t instruction = (code[0] << 8) | code[1];

    return instruction;

}

int main(int argc, char**argv) {
    state = load_rom(argc, argv);

    Display SDL_display = Display(argv[1]);
    // state.draw_flag = true;


    SDL_Event window_event;

    uint64_t i = 0;
    state.PC = 0x200;
    array<uint32_t, WIDTH * HEIGHT> display_arr_new = state.display_array;
    while (state.PC < 4096) // && i < 100000)
    {
        cout << i << ": ";
        uint16_t ins = fetch();        
        decode(ins);
        while(SDL_PollEvent(&window_event) | state.draw_flag) {
            if (window_event.type == SDL_QUIT) exit(0);
            else if(window_event.type == SDL_KEYDOWN) {
                for (int i = 0; i < 16; ++i) {
                    if (window_event.key.keysym.sym == KEYMAP[i]) {
                        state.K = i;
                    }
                }
            }
            else if(window_event.type == SDL_KEYUP) {
                for (int i = 0; i < 16; ++i) {
                    if (window_event.key.keysym.sym == KEYMAP[i]) {
                        state.K = 0;
                    }
                }
            }            

        }
        if (state.draw_flag){
            state.draw_flag = false;
            cout << "DRAWING" << endl;
            // sleep_for(std::chrono::microseconds(1200));
            display_arr_new = SDL_display.render(state.display_array);
            // state.display_array[i%state.display_array.size()] = 1;
        }

        state.display_array = display_arr_new;
        sleep_for(std::chrono::microseconds(1200));
        state.PC += 2; 

        i++; 
    }    

    
    return 0;
}
