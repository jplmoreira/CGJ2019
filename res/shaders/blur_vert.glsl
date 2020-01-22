#version 330 core

in vec3 in_position;
in vec2 in_texcoord;

out vec2 o_texcoord;

void main() {  //apenas passamos coordenadas de textura e a posicao do quad para blurring
	o_texcoord = in_texcoord;
	gl_Position = vec4(in_position, 1.0);
}