#version 330 core

in vec3 in_position;
in vec2 in_texcoord;

out vec2 o_texcoord;

void main() {
	o_texcoord = in_texcoord; //passamos so as coordenadas de textura
	gl_Position = vec4(in_position, 1.0);
}