#include <iostream>
#include "../projectResources.h"
#include "components/window.h"
#include "components/gameObjects/brick.h"
#include "managers/resourceManager.h"

#include "openGL/renderer.h"
#include "openGL/shader.h"
#include "openGL/Texture2D.h"

int main(void) {
	Window window("Arkanoid (c) A. Urbanyk", 800, 800);
	Game game{};
    {
		ResourceManager::loadShader(BASIC_SHADER, "basic");
		ResourceManager::loadTexture2D(SAMPLE_TEXTURE, "sample_texture");
		Renderer renderer;
		Brick brick(glm::vec2(100.0f, 50.0f), "sample_texture", "basic", glm::vec2(0.5f, 0.5f));
		
		Shader* basicShader = ResourceManager::getShader("basic");
		basicShader->bind();

		Texture2D* texture = ResourceManager::getTexture2D( "sample_texture");
		texture->bind();
		basicShader->setUniform1i("u_Texture", 0);

		basicShader->unbind();
    	
	    /* Loop until the user closes the window */
	    while (!glfwWindowShouldClose(window.getWindowPointer())) {

	        /* Render here */
			renderer.clear();

			renderer.draw(brick);

	        /* Swap front and back buffers */
	        glCall(glfwSwapBuffers(window.getWindowPointer()));

	        /* Poll for and process events */
	        glCall(glfwPollEvents());
	    }
	}
	
    return 0;
}
