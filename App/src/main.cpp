#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaderCreator.h"

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW wasn't initialized!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f, // 0
         0.5f, -0.5f, // 1
         0.5f,  0.5f, // 2
    	-0.5f,  0.5f, // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao; // prepare buffer (vertex array object)
    glGenBuffers(1, &vao); // generate new buffer with size = 1
    glBindBuffer(GL_ARRAY_BUFFER, vao); // bind our buffer to STATE MACHINE GL_ARRAY_BUFFER = for vertex attributes
	
    /*
     * GL_ARRAY_BUFFER - which the buffer object is bound, 6 - count of values
     * positions - pointer to our dataArr, GL_STATIC_DRAW - how we should use that data (how a buffer object's data store will be accessed.)
     */
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0); // enable vertex attributes Array
	
    /**
     *  0 - position, 2 - size (1 vert = 2 floats), GL_FLOAT - what kind of data we use,
     *  GL_FALSE - normalization, stride - how many bites takes one vert, pointer - begining of our first vert
     */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    const unsigned int shader = createShader("res/shaders/main.shader");
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    	
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}