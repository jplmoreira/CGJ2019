#version 330 core

in vec4 in_position;
in vec4 in_color;
out vec4 ex_color;

uniform mat4 ModelMatrix;

void main(void) {
	gl_Position = ModelMatrix * in_position;
	ex_color = in_color;
}