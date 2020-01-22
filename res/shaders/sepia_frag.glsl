#version 330 core

out vec4 frag_color;

in vec2 o_texcoord;

uniform bool toggle;
uniform sampler2D image;  //textura do render normal para aplicar o sepia

void main() {
	vec3 tex_color = texture(image, o_texcoord).rgb;  //vamos buscar o rgb da coordenada de textura
	if (toggle) { //se sepia ligado
		float output_red = (tex_color.r * .393) + (tex_color.g *.769) + (tex_color.b * .189);   //mudamos r, g e b de acordo com a formula
		float output_green = (tex_color.r * .349) + (tex_color.g *.686) + (tex_color.b * .168);
		float output_blue = (tex_color.r * .272) + (tex_color.g *.534) + (tex_color.b * .131);
		frag_color = vec4(output_red, output_green, output_blue, 1.0);                         //out frag color vai ser o resultado alterado do rgb
	} else
		frag_color = vec4(tex_color, 1.0);  //Caso contrario output normal
} 

