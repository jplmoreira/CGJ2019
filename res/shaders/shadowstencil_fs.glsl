#version 330 core

in vec3 o_normal;

out vec4 frag_color;

void main(void) {
	vec3 axis = vec3(0.0, 1.0, 0.0);

	bvec3 eq = equal(axis, o_normal);
	if (!eq.x || !eq.y || !eq.z)
		discard;

	frag_color = vec4(1.0);
}