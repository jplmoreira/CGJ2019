#version 330 core

uniform vec4 in_color;

in vec3 o_position;
in vec2 o_texcoord;

out vec4 frag_color;

float interpolate(float v1, float v2, float t) {  //interpolamos dois valores consoante o t, t é o U das tex coords. v1 e v2 sao os valores p interpolar
	float interval = 0.15;   //frequencia da interpolacao
	while (t > interval) {   //Se o t for maior, retiramos o intervalo até dar para "recomeçar" a interpolar
		t -= interval;
	}
	t /= interval;   //dividimos o t pelo intervalo
	return (1.0-t) * v2 + t * v1; //interpolamos consoante T
}

void main(void) {
	frag_color = vec4(interpolate(in_color.x, 0.1, o_texcoord.x), interpolate(in_color.y, 0.1, o_texcoord.x), interpolate(in_color.z, 0.1, o_texcoord.x), 1.0);
}  //Devolvemos como out frag color os valores de r g b interpolados