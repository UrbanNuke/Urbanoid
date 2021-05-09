#pragma once

class Texture2D {
	unsigned int m_RendererId;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BitsPerPixel;

public:

	Texture2D(const unsigned int texture2D);
	~Texture2D();

	void bind(const unsigned int slot = 0) const;
	void unbind() const;

	inline unsigned int getWidth() const { return m_Width; }
	inline unsigned int getHeight() const { return m_Height; }
};
