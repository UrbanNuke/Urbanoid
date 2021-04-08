#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "components/shaderCreator.h"
#include "components/renderer.h"
#include "../projectResources.h"
#include "components/indexBufferObj.h"
#include "components/vertexBufferObj.h"


int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Arkanoid (c) A.Urbanyk", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW wasn't initialized!" << std::endl;
    }
	
    {
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

	    unsigned int vao; // prepare vertex array object
	    glCall(glGenVertexArrays(1, &vao));
	    glCall(glBindVertexArray(vao));

	    VertexBufferObj vbo(positions, 4 * 2 * sizeof(float));
	    glCall(glEnableVertexAttribArray(0)); // enable vertex attributes Array

	    /**
	     *  0 - position, 2 - size (1 vert = 2 floats), GL_FLOAT - what kind of data we use,
	     *  GL_FALSE - normalization, stride - how many bites takes one vert, pointer - begining of our first vert
	     */
	    glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

	    IndexBufferObj ibo(indices, 6);

	    const unsigned int shader = createShader(BASIC_SHADER);
	    glCall(glUseProgram(shader));

	    glCall(const int location = glGetUniformLocation(shader, "u_Color"));
	    _ASSERT(location != -1);
	    glCall(glUniform4f(location, 0.8f, 0.5f, 0.2f, 1.0f));

	    glCall(glBindVertexArray(0));
	    glCall(glUseProgram(0));
	    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	    float increment = 0.05f;
	    float r = 0.0f;

	    /* Loop until the user closes the window */
	    while (!glfwWindowShouldClose(window)) {

	        /* Render here */
	        glCall(glClear(GL_COLOR_BUFFER_BIT));

	        glCall(glUseProgram(shader));
	        glCall(glUniform4f(location, r, 0.5f, 0.2f, 1.0f));

	        glCall(glBindVertexArray(vao));
	        ibo.Bind();
	        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	        if (r > 1.0f) {
	            increment = -0.05f;
	        } else if (r < 0.0f) {
	            increment = 0.05f;
	        }

	        r += increment;

	        /* Swap front and back buffers */
	        glCall(glfwSwapBuffers(window));

	        /* Poll for and process events */
	        glCall(glfwPollEvents());
	    }

	    glCall(glDeleteProgram(shader));
	}

    glfwTerminate();
    return 0;
}
