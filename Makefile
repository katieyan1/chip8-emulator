SRC_DIR = .
BUILD_DIR = build/debug
CC = clang++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cxx)
OBJ_NAME = output
# INCLUDE_PATHS = -Iinclude 
INCLUDE_PATHS = -I/Library/Frameworks/SDL2.framework/Headers
# INCLUDE_PATHS = -I./SDL2/include/ #-I/opt/homebrew/Cellar/sdl2_image/2.8.2_1/include/SDL2
# LIBRARY_PATHS = -Llib
# LIBRARY_PATHS = -l./SDL2/ #-l/opt/homebrew/Cellar/sdl2/2.30.2/lib/SDL2 #-l/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib/SDL2
FRAMEWORK_PATHS = -F/Library/Frameworks
FRAMEWORKS = -framework SDL2
RPATH =  -rpath /Library/Frameworks/

COMPILER_FLAGS = -std=c++17 -Wall -O0 -g
# LINKER_FLAGS = -lsdl2 -lsdl2_image

all:
	# $(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)
	# clang++ simplewindow.cxx -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -rpath /Library/Frameworks/ -o simplewindow.out
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(FRAMEWORK_PATHS) $(FRAMEWORKS) $(SRC_FILES) $(RPATH) -o ./$(OBJ_NAME)

