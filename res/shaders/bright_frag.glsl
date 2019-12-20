#version 330 core

uniform vec4 in_color;

in vec3 o_position;
in vec3 o_normal;
in vec2 o_texcoord;

layout (location = 0) out vec4 frag_color;
layout (location = 1) out vec4 bright_color;

void main(void) {
	frag_color = in_color;
	bright_color = in_color;
}