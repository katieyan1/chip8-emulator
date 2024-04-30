#include "input.h"


Input::Input() {
    keys.fill(0);
    get_keyboard();
    previous_keys = current_keys;
}

Input::~Input() = default;

void Input::update() {
    previous_keys = current_keys;
    get_keyboard();
}

void Input::get_keyboard() {
    auto output = SDL_GetKeyboardState(nullptr);
    current_keys = vector<uint8_t>(output, output+322);
}

uint8_t Input::get_key(SDL_Scancode sc) {
    return (uint8_t) (previous_keys[sc] && current_keys[sc]);
}

/* */
void Input::handle_input() {
    keys[0] = get_key(SDL_SCANCODE_1);
    keys[1] = get_key(SDL_SCANCODE_2);
    keys[2] = get_key(SDL_SCANCODE_3);
    keys[3] = get_key(SDL_SCANCODE_4);
    
    keys[4] = get_key(SDL_SCANCODE_Q);
    keys[5] = get_key(SDL_SCANCODE_W);
    keys[6] = get_key(SDL_SCANCODE_E);
    keys[7] = get_key(SDL_SCANCODE_R);

    keys[8] = get_key(SDL_SCANCODE_A);
    keys[9] = get_key(SDL_SCANCODE_S);
    keys[10] = get_key(SDL_SCANCODE_D);
    keys[11] = get_key(SDL_SCANCODE_F);

    keys[12] = get_key(SDL_SCANCODE_Z);
    keys[13] = get_key(SDL_SCANCODE_X);
    keys[14] = get_key(SDL_SCANCODE_C);
    keys[15] = get_key(SDL_SCANCODE_V);
}