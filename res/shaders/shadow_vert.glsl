#version 330 core

in vec3 in_position;

uniform mat4 ModelMatrix;
uniform mat4 ShadowProjMat;

uniform SharedMatrices {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void) {
	gl_Position = ProjectionMatrix * ViewMatrix * ShadowProjMat * ModelMatrix * vec4(in_position, 1.0);
}