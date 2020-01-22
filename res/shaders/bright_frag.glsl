#version 330 core

uniform sampler2D tex;

in vec3 o_position;
in vec3 o_normal;
in vec2 o_texcoord;

layout (location = 0) out vec4 frag_color;    //multi target rendering para sacar duas texturas numa só passada
layout (location = 1) out vec4 bright_color;

void main(void) {
	vec3 result = texture(tex, o_texcoord).rgb;              //vamos buscar o rgb da coordenada de textura
	frag_color = vec4(result, 1.0);                          //criamos o frag color desse rgb em vec4 - render normal
	float brightness = dot(result, vec3(0.25, 0.75, 0.1));   //encontramos o nivel de brightness do fragmento em questao
	if (brightness > 1.0)                                    //de acordo com  o threshold
		bright_color = vec4(result, 1.0);                    //pintamos da sua propria cor  - render das partes bright
	else
		bright_color = vec4(0.0, 0.0, 0.0, 1.0);			 //ou de preto  - render das partes bright
}