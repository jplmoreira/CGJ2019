#version 330 core

out vec4 frag_color;

in vec2 o_texcoord;

uniform sampler2D scene;
uniform sampler2D bloom_blur;

void main() {
	vec3 hdr_color = texture(scene, o_texcoord).rgb;
	vec3 bloom_color = texture(bloom_blur, o_texcoord).rgb;
	hdr_color += bloom_color;
	frag_color = vec4(hdr_color, 1.0);
} 