#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../projectResources.h"

#include "components/renderer.h"
#include "components/indexBufferObj.h"
#include "components/shader.h"
#include "components/vertexArrayObj.h"
#include "components/vertexBufferLayout.h"
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
    glfwSwapInterval(3);

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

		VertexArrayObj vao;
		VertexBufferObj vbo(positions, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.push<float>(2);
		vao.addVertexBufferObj(vbo, layout);

	    IndexBufferObj ibo(indices, 6);

		Shader basicShader(BASIC_SHADER);
		basicShader.bind();
		basicShader.setUniform4f("u_Color", 0.8f, 0.5f, 0.2f, 1.0f);

		vao.unbind();
		vbo.unbind();
		ibo.unbind();
		basicShader.unbind();

	    float increment = 0.05f;
	    float r = 0.0f;

	    /* Loop until the user closes the window */
	    while (!glfwWindowShouldClose(window)) {

	        /* Render here */
	        glCall(glClear(GL_COLOR_BUFFER_BIT));

			basicShader.bind();
			basicShader.setUniform4f("u_Color", r, 0.5f, 0.2f, 1.0f);

			vao.bind();
	        ibo.bind();
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
	}

    glfwTerminate();
    return 0;
}
