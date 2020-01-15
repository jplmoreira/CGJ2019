#version 330 core

in vec3 in_position;
in vec3 in_normal;
out vec3 o_normal;

uniform mat4 ModelMatrix;

uniform SharedMatrices {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void) {
	mat3 NormalMatrix = transpose(inverse(mat3(ModelMatrix)));
	o_normal = normalize(NormalMatrix * in_normal);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);
}