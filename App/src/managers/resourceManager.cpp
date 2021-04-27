#include "resourceManager.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../res/resource.h"
#include "../openGL/renderer.h"

std::unordered_map<std::string, Shader*> ResourceManager::s_Shaders;
std::unordered_map<std::string, Texture2D*> ResourceManager::s_Textures2D;

glm::vec4 ResourceManager::s_RedColor = glm::vec4(0.75f, 0.0f, 0.0f, 1.0f);
glm::vec4 ResourceManager::s_GreenColor = glm::vec4(0.38f, 0.88f, 0.0f, 1.0f);
glm::vec4 ResourceManager::s_LightBlueColor = glm::vec4(0.38f, 0.5f, 0.63f, 1.0f);
glm::vec4 ResourceManager::s_YellowColor = glm::vec4(0.88f, 0.88f, 0.0f, 1.0f);
glm::vec4 ResourceManager::s_PinkColor = glm::vec4(0.75f, 0.25f, 0.63f, 1.0f);
std::map<unsigned char, ResourceManager::Character>  ResourceManager::s_Characters;

Shader* ResourceManager::loadShader(const unsigned int shader, const std::string& name) {
	Shader* newShader = new Shader(shader);
	s_Shaders[name] = newShader;
	return s_Shaders[name];
}

Shader* ResourceManager::getShader(const std::string& name) {
	if (s_Shaders.find(name) == s_Shaders.end()) {
		ASSERT(false);
	}
	return s_Shaders[name];
}

Texture2D* ResourceManager::loadTexture2D(const unsigned int texture, const std::string& name) {
	Texture2D* newTexture2D = new Texture2D(texture);
	s_Textures2D[name] = newTexture2D;
	return s_Textures2D[name];
}

Texture2D* ResourceManager::getTexture2D(const std::string& name) {
	if (s_Textures2D.find(name) == s_Textures2D.end()) {
		ASSERT(false);
	}
	return s_Textures2D[name];
}

void ResourceManager::loadFont(const unsigned int font) {
    const Resource res = Resource(font, "FONT_");
    const std::string tex = std::string(res.GetResourceString());

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    FT_Face face;

    if (FT_New_Memory_Face(ft, (unsigned char*)tex.c_str(), res.GetResourceString().size(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); // Disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; ++c) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))     {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        unsigned int texture;
        glCall(glGenTextures(1, &texture));
        glCall(glBindTexture(GL_TEXTURE_2D, texture));
        glCall(glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
            0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer)
        );
        // Set texture options
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        // Now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        s_Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void ResourceManager::clear() {
	// (properly) delete all shaders
	for (auto [name, shader] : s_Shaders) {
		delete shader;
	}

	for (auto [name, texture] : s_Textures2D) {
		delete texture;
	}

	s_Shaders.clear();
	s_Textures2D.clear();
    s_Characters.clear();
}
