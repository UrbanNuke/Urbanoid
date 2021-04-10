#include <iostream>
#include "../projectResources.h"
#include "components/window.h"
#include "managers/resourceManager.h"

#include "openGL/renderer.h"
#include "openGL/indexBufferObj.h"
#include "openGL/shader.h"
#include "openGL/vertexArrayObj.h"
#include "openGL/vertexBufferLayout.h"
#include "openGL/vertexBufferObj.h"


int main(void) {
	Window window("Arkanoid (c) A. Urbanyk", 800, 800);
	
    {

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
		
		Shader basicShader = ResourceManager::loadShader(BASIC_SHADER, "basic");
		basicShader.bind();
		basicShader.setUniform4f("u_Color", 0.8f, 0.5f, 0.2f, 1.0f);

		vao.unbind();
		vbo.unbind();
		ibo.unbind();
		basicShader.unbind();

	    float increment = 0.05f;
	    float r = 0.0f;

		Renderer renderer;
    	
	    /* Loop until the user closes the window */
	    while (!glfwWindowShouldClose(window.getWindowPointer())) {

	        /* Render here */
			renderer.clear();

			basicShader.bind();
			basicShader.setUniform4f("u_Color", r, 0.5f, 0.2f, 1.0f);

			renderer.draw(vao, ibo, basicShader);

	        if (r > 1.0f) {
	            increment = -0.05f;
	        } else if (r < 0.0f) {
	            increment = 0.05f;
	        }

	        r += increment;

	        /* Swap front and back buffers */
	        glCall(glfwSwapBuffers(window.getWindowPointer()));

	        /* Poll for and process events */
	        glCall(glfwPollEvents());
	    }
	}
	
    return 0;
}
