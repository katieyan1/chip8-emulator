#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <sys/mman.h>
#include <sys/stat.h>
#include "elf.h"
#include "globals.h"

#include <array>
using namespace std;

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
    uint64_t fsize = ftell(f);    
    fseek(f, 0L, SEEK_SET);

    uint8_t buffer[fsize];
    fread(buffer, fsize, 1, f);
    fclose(f);

    uint64_t pc = 0x0;    
    std::copy(buffer, buffer + fsize, memory.begin());
    return Chip8State(memory, fsize);
}
