#version 330 core

in vec3 in_position;
in vec2 in_texcoord;
out vec3 o_position;
out vec2 o_texcoord;

uniform mat4 ModelMatrix;

uniform SharedMatrices {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void) {
	o_position = vec3(ModelMatrix * vec4(in_position, 1.0));
	o_texcoord = in_texcoord;

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);
}