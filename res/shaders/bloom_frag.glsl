#version 330 core

out vec4 frag_color;

in vec2 o_texcoord;

uniform sampler2D scene; //textura do render normal
uniform sampler2D bloom_blur; //textura da brightness já blurred

void main() {
    const float gamma = 2.2; 
	const float exposure = 2.5;
	vec3 hdr_color = texture(scene, o_texcoord).rgb;         //cor rgb do render normal
	vec3 bloom_color = texture(bloom_blur, o_texcoord).rgb;  //cor rgb do render da brightness depois do blur
	bvec3 gt1 = greaterThan(hdr_color, vec3(0.1,0.1,0.1));   //cor mais clara do que background?
	bvec3 gt2 = greaterThan(bloom_color, vec3(0.1,0.1,0.1)); //same para a textura blurred
	vec3 result;
	if ((gt1.x || gt1.y || gt1.z) && (gt2.x || gt2.y || gt2.z)) //se ambos nao forem background color
		result = hdr_color;                                     //mantemos o fragmento "original"
	else if (gt2.x || gt2.y || gt2.z)                           //se só o blurred nao for background color
		result = bloom_color;                                   //pintamos da cor blurred
	else                                                        //caso contrario
		result = hdr_color;                                     //pintamos da bg color
	frag_color = vec4(result, 1.0);                             //out frag color é o resultado da condicao
} 