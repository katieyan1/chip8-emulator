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

// struct elf_header {
//     uint8_t ignore_1[24];
//     uint64_t entry;
//     uint64_t prog_header_offset;
//     uint8_t ignore_2[14];
//     uint16_t program_header_entry_size;
//     uint16_t program_header_entry_count;
// };

// struct program_header {
//     uint32_t type;
//     uint32_t flags;
//     uint64_t offset;
//     uint64_t vaddr;
//     uint64_t paddr;
//     uint64_t filesz;
//     uint64_t memsz;
// };

// uint64_t loadElf(char const * const fileName) {
//     int fd = open(fileName,O_RDONLY);
//     if (fd < 0) {
//         perror(fileName);
//         exit(-1);
//     }
    
//     struct stat statBuffer;
//     int rc = fstat(fd,&statBuffer);
//     if (rc != 0) {
//         perror("stat");
//         exit(-1);
//     }

void load_rom (int argc, char**argv){
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
    state = Chip8State(memory, fsize);
}
