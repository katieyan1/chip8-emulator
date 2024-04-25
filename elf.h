#pragma once
#include "chip8state.h"
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

Chip8State load_rom(int argc, char **argv);
