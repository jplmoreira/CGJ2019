#version 330 core

out vec4 frag_color;

in vec2 o_texcoord;

uniform sampler2D scene;
uniform sampler2D bloom_blur;

void main() {
    const float gamma = 2.2;
	const float exposure = 2.5;
	vec3 hdr_color = texture(scene, o_texcoord).rgb;
	vec3 bloom_color = texture(bloom_blur, o_texcoord).rgb;
	bvec3 gt1 = greaterThan(hdr_color, vec3(0.1,0.1,0.1));
	bvec3 gt2 = greaterThan(bloom_color, vec3(0.1,0.1,0.1));
	vec3 result;
	if ((gt1.x || gt1.y || gt1.z) &&
		(gt2.x || gt2.y || gt2.z))
		result = hdr_color;
	else if (gt2.x || gt2.y || gt2.z)
		result = bloom_color;
	else
		result = hdr_color;
	frag_color = vec4(result, 1.0);
} 