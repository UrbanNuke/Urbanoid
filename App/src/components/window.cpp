#include "window.h"
#include <iostream>
#include "../openGL/renderer.h"

/**
 * \brief Create a window
 * \param windowName window's name
 * \param width window's width
 * \param height window's height
 */
Window::Window(const std::string& windowName, const unsigned int width, const unsigned int height)
{
    /* Initialize the library */
    if (!glfwInit())
        ASSERT(false);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        ASSERT(false);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(3);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW wasn't initialized!" << std::endl;
        ASSERT(false);
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
    glfwTerminate();
}

void Window::launchGameLoop(Game& game) {
}
