#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <Windows.h>

int main() {
    glfwInit();
    POINT p;
    GetCursorPos(&p);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //GLFWcursor* cursor = new GLFWcursor;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
    //glfwSetCursor(window, cursor);
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        GetCursorPos(&p);
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if(xpos > 0 && ypos > 0 && xpos < 800 && ypos < 600)
        std::cout << xpos << " " << ypos << std::endl;
    }
    
    
    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}