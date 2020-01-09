#version 330 core

out vec4 frag_color;

in vec2 o_texcoord;

uniform sampler2D scene;
uniform sampler2D bloom_blur;

void main() {
	const float gamma = 2.2;
	vec3 hdr_color = texture(scene, o_texcoord).rgb;
	vec3 bloom_color = texture(bloom_blur, o_texcoord).rgb;
	hdr_color += bloom_color;
	//tone mapping
	vec3 result = vec3(1.0) - exp(-hdr_color);
	//gamma correction
	result = pow(result, vec3(1.0 / gamma));
	frag_color = vec4(result, 1.0);
} 