#version 330 core

uniform vec4 in_color;

in vec3 o_position;
in vec2 o_texcoord;

out vec4 frag_color;

float interpolate(float v1, float v2, float t) {
	float interval = 0.15;
	while (t > interval) {
		t -= interval;
	}
	t /= interval;
	return (1.0-t) * v2 + t * v1;
}

void main(void) {
	frag_color = vec4(interpolate(in_color.x, 0.1, o_texcoord.x), interpolate(in_color.y, 0.1, o_texcoord.x), interpolate(in_color.z, 0.1, o_texcoord.x), 1.0);
}