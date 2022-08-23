#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "GAME_RENDERER.h"
int main() {
    GAME_RENDERER::GAME_RENDERER rnd(1000, 800, "PLATFORMER");
    rnd.run();
    return EXIT_SUCCESS;
}