#version 330 core

uniform sampler2D tex;

in vec3 o_position;
in vec3 o_normal;
in vec2 o_texcoord;

layout (location = 0) out vec4 frag_color;
layout (location = 1) out vec4 bright_color;

void main(void) {
	vec3 result = texture(tex, o_texcoord).rgb;
	frag_color = vec4(result, 1.0);
	float brightness = dot(result, vec3(0.25, 0.75, 0.1));
	if (brightness > 1.0)
		bright_color = vec4(result, 1.0);
	else
		bright_color = vec4(0.0, 0.0, 0.0, 1.0);
}