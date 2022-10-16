#include <iostream>
#include <cstdlib>
#include <stdexcept>



#include "GAME_RENDERER.h"
int main() {
    GAME_RENDERER::GAME_RENDERER rnd(1600, 900, "PLATFORMER");
    rnd.run();
    return EXIT_SUCCESS;
}