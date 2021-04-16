#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform vec4 u_Position;
uniform mat4 u_Projection;

void main() {
	gl_Position = u_Projection * vec4(position.x + u_Position.x, position.y + u_Position.y, 0.0f, 1.0f);
	v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color = vec4(0.69f, 0.15f, 0.76f, 1.0f); //pink color by default
uniform sampler2D u_Texture;

void main() {

	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;
}