#version 330 core

in vec3 in_position;
in vec3 in_normal;
in vec2 in_texcoord;
out vec3 o_position;
out vec3 o_normal;
out vec2 o_texcoord;

uniform mat4 ModelMatrix;

uniform SharedMatrices {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void) {
	o_position = vec3(ModelMatrix * vec4(in_position, 1.0));   //posi�ao em model space
	o_texcoord = in_texcoord;								   //passamos coordenadas de textura

	mat3 NormalMatrix = transpose(inverse(mat3(ModelMatrix))); //para atualizar as normais
	o_normal = normalize(NormalMatrix * in_normal);            //a normal em view space

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_position, 1.0);  //posi�ao do vertex em pvm clip space
}