#include "window.h"
#include <iostream>
#include "../openGL/renderer.h"

Window::Window(const std::string& windowName, const unsigned int width, const unsigned int height)
	: m_GLFWWindow(nullptr), m_Game(nullptr), Width(width), Height(height)
{
    /* Initialize the library */
    if (!glfwInit())
        ASSERT(false);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    m_GLFWWindow = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (!m_GLFWWindow) {
        glfwTerminate();
        ASSERT(false);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_GLFWWindow);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW wasn't initialized!" << std::endl;
        ASSERT(false);
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    glfwSetWindowUserPointer(m_GLFWWindow, this);

    m_Game = new Game(width, height);
}

Window::~Window() {
    glfwTerminate();
}

void Window::launchGameLoop() const {
    m_Game->init();

    float dt = 0.0f;
    float lastFrame = 0.0f;

    glfwSetKeyCallback(m_GLFWWindow, keyCallback);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_GLFWWindow)) {
        m_Game->getRenderer()->clear();
        /* Render here */

        // dt calculations
        const float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
       
        m_Game->input(dt);
        m_Game->update(dt);

        m_Game->collisionCheck();

        m_Game->render();

        /* Swap front and back buffers */
        glCall(glfwSwapBuffers(m_GLFWWindow));


        /* Poll for and process events */
        glCall(glfwPollEvents());
    }
}

void Window::keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	
	if (action == GLFW_PRESS) {
		window->m_Game->keyDown(key);
	}
	if (action == GLFW_RELEASE) {
        window->m_Game->keyUp(key);
	}
}


