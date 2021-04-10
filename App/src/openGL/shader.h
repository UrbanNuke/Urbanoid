#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
	unsigned int m_RendererId;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
                   Shader(const unsigned int shader);
	~Shader();

	void bind() const;
	void unbind() const;

	//Set uniforms
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	unsigned int getUniformLocation(const std::string& name);
	unsigned int compileShader(const unsigned int type, const std::string& source);
	unsigned int createShader(unsigned int shader);
	ShaderProgramSource parseShader(const std::string_view& shader) const;
};

