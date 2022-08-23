#include <iostream>
#include "FIRST_APP.hpp"
#include <cstdlib>
#include <stdexcept>

int main() {
    lve::FirstApp app{};

    try {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}