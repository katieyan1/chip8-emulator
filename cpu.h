#pragma once
#include "chip8state.h"
#include "elf.h"
#include <fcntl.h>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <sys/mman.h>
#include <sys/stat.h>
#include <array>
#include <iostream>
#include <iomanip>

using std::array;
using std::cout;
using std::endl;
using std::hex;
using std::setw;
using std::setfill;

void decode(uint16_t instruction);
void fetch(Chip8State state);