#version 330 core

uniform vec4 in_color;

in vec3 o_position;
in vec3 o_normal;
in vec2 o_texcoord;

out vec4 frag_color;

void main(void) {
	vec3 light_pos = vec3(5.0, 5.0, 5.0);
	vec3 light_color = vec3(1.0, 1.0, 1.0);

	float ambient_strength = 0.25;
	vec3 ambient = ambient_strength * light_color;

	vec3 norm = normalize(o_normal);
	vec3 light_dir = normalize(light_pos - o_position);
	float diff = max(dot(norm, light_dir), 0.0);
	vec3 diffuse = diff * light_color;

	vec3 res = (ambient + diffuse) * vec3(in_color);
	frag_color = vec4(res, 1.0);
}