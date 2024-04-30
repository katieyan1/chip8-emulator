SRC_DIR = .
BUILD_DIR = build/debug
CC = clang++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cxx)
OBJ_NAME = output
INCLUDE_PATHS = -I/Library/Frameworks/SDL2.framework/Headers
FRAMEWORK_PATHS = -F/Library/Frameworks
FRAMEWORKS = -framework SDL2
RPATH =  -rpath /Library/Frameworks/

COMPILER_FLAGS = -std=c++17 -Wall -O0 -g

all:
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(FRAMEWORK_PATHS) $(FRAMEWORKS) $(SRC_FILES) $(RPATH) -o ./$(OBJ_NAME)

