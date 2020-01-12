#version 330 core

uniform sampler2D tex;

in vec3 o_position;
in vec3 o_normal;
in vec2 o_texcoord;

out vec4 frag_color;

void main(void) {
	frag_color = texture(tex, o_texcoord);
}