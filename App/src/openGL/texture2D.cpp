#include <GL/glew.h>

#include "renderer.h"
#include "texture2D.h"
#include "../../res/resource.h"
#include "stb_image/stb_image.h"

Texture2D::Texture2D(const unsigned texture2D)
	: m_RendererId(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BitsPerPixel(0)
{
	stbi_set_flip_vertically_on_load(1);
	Resource res(texture2D, "TEXTURE");
	std::string tex = std::string(res.GetResourceString());
	m_LocalBuffer = stbi_load_from_memory(
		(unsigned char*)tex.c_str(), tex.size(), &m_Width, &m_Height,  &m_BitsPerPixel, 4
	);
	
	glCall(glGenTextures(1, &m_RendererId));
	glCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	glCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}

Texture2D::~Texture2D() {
	glCall(glDeleteTextures(1, &m_RendererId));
}

void Texture2D::bind(const unsigned int slot) const {
	glCall(glActiveTexture(GL_TEXTURE0 + slot));
	glCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture2D::unbind() const {
	glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
