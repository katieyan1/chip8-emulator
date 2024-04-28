#include <sys/mman.h>
#include <sys/stat.h>
#include <array>
#include <vector>
#include <SDL2/SDL.h>

using std::array;
using std::vector;

class Input {
    public:
        array<uint8_t, 16> keys;
        vector<uint8_t> current_keys;
        vector<uint8_t> previous_keys;
    
    Input();
    ~Input();
    void update();
    void get_keyboard();
    uint8_t get_key(SDL_Scancode sc);
    void handle_input();
};