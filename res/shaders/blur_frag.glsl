#version 330 core

out vec4 frag_color;

in vec2 o_texcoord;

uniform sampler2D image;   //textura que vamos fazer blur
uniform bool horizontal;   //passamos a flag para o shader para saber qual o blur a fazer
uniform float weight[5] = float[] (0.22702702370, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162); //learn opengl 

void main() {
	vec2 tex_offset = 1.0 / textureSize(image, 0);
	vec3 result = texture(image, o_texcoord).rgb * weight[0];

	if (horizontal) {  //blur no x
		for (int i = 1; i < 5; i++) {
			result += texture(image, o_texcoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
			result += texture(image, o_texcoord - vec2(tex_offset.x * i, 0.0)).rbg * weight[i];
		}
	}
	else { // blur no y
		for (int i = 1; i < 5; i++) {
			result += texture(image, o_texcoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
			result += texture(image, o_texcoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
		}
	}
	frag_color = vec4(result, 1.0); //valor do fragmento resultante do blur feito
}