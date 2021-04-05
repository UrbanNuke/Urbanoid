#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main() {
	gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color = vec4(0.69f, 0.15f, 0.76f, 1.0f); //pink color by default

void main() {
	color = u_Color;
}