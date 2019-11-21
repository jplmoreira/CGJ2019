#version 330 core

in vec3 in_position;
in vec3 in_normal;
in vec2 in_texcoord;
out vec4 ex_color;

uniform vec4 in_color;
uniform mat4 ModelMatrix;

uniform SharedMatrices {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void) {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0f);
    ex_color = in_color;
}