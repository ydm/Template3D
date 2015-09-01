#version 450 core

// Stage inputs
layout (location = 0) in vec3 i_normal;

// Stage outputs
layout (location = 0 ) out vec3 o_color;

// Light position
const vec3 lightPosition = vec3(20.0, 20.0, 20.0);
const vec3 lightVector = normalize(lightPosition);
const vec3 lightColor = vec3(0.996078431373, 0.952941176471, 0.917647058824);  // True color of the sun ;)

// Object's diffuse color
const vec3 diffuseColor = vec3(0.5, 1.0, 1.0);

float computeDiffuseShading(in vec3 normal)
{
	const float d = dot(normal, lightVector);
	if (d < 0) {
		return 0;
	}
	return d;
}

// Main
void main(void)
{
	// o_color = normalize(i_normal);
	const float d = computeDiffuseShading(i_normal);
	const vec3 dv = vec3(d, d, d);
	o_color = dv * lightColor * diffuseColor;
}
