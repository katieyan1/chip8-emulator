#include "elf.h"

Chip8State load_rom (int argc, char**argv){
    array<uint8_t, 4096> memory;
    FILE *f = fopen(argv[1], "rb");
    if (f==NULL)    
    {    
        printf("error: Couldn't open %s\n", argv[1]);    
        exit(1);    
    }    

    //Get the file size    
    fseek(f, 0L, SEEK_END);    
    uint64_t rom_size = ftell(f);    
    fseek(f, 0L, SEEK_SET);

    // Allocate memory to store rom
    char* rom_buffer = (char*) malloc(sizeof(char) * rom_size);
    if (rom_buffer == NULL) {
        std::cerr << "Failed to allocate memory for ROM" << std::endl;
    }

    // Copy ROM into buffer
    size_t result = fread(rom_buffer, sizeof(char), (size_t)rom_size, f);
    if (result != rom_size) {
        std::cerr << "Failed to read ROM" << std::endl;
    }

    // Copy buffer to memory
    if ((4096-512) > rom_size){
        for (int i = 0; i < rom_size; ++i) {
            memory[i + 512] = (uint8_t)rom_buffer[i];   // Load into memory starting
                                                        // at 0x200 (=512)
        }
    }
    else {
        std::cerr << "ROM too large to fit in memory" << std::endl;
    }

    // Clean up
    fclose(f);
    free(rom_buffer);

    return Chip8State(memory, rom_size);
}
