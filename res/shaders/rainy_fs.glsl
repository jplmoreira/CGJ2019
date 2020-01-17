#version 330 core

uniform vec4 in_color;

in vec3 o_position;
in vec3 o_normal;
in vec2 o_texcoord;

out vec4 frag_color;

void main(void) {
	frag_color = in_color;
}