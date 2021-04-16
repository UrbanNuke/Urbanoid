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
	: m_Window(nullptr), m_Game(nullptr), Width(width), Height(height)
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

    m_Game = new Game(width, height);
}

Window::~Window() {
    glfwTerminate();
}

void Window::launchGameLoop() const {
    m_Game->init();
    
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_Window)) {
        m_Game->getRenderer()->clear();
        /* Render here */
       
        m_Game->input();
        m_Game->update();

        m_Game->collisionCheck();

        m_Game->render();

        /* Swap front and back buffers */
        glCall(glfwSwapBuffers(m_Window));


        /* Poll for and process events */
        glCall(glfwPollEvents());
    }
}
