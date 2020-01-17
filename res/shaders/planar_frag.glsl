#version 330 core

uniform vec4 in_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

in vec3 o_position;
in vec3 o_normal;
in vec2 o_texcoord;

out vec4 frag_color;

void main(void) {
	vec3 light_color = vec3(1.0, 1.0, 1.0);
	float specular_strength = 0.5;

	float ambient_strength = 0.25;
	vec3 ambient = ambient_strength * light_color;

	vec3 norm = normalize(o_normal);
	vec3 light_dir = normalize(light_pos - o_position);
	float diff = max(dot(norm, light_dir), 0.0);
	vec3 diffuse = diff * light_color;

	vec3 view_dir = normalize(view_pos - o_position);
	vec3 ref_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, ref_dir), 0.0), 32);
	vec3 specular = specular_strength * spec * light_color;

	vec3 res = (ambient + diffuse + specular) * vec3(in_color);
	frag_color = vec4(res, 1.0);
}