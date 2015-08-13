#version 450 core

// Uniforms
uniform sampler2D u_sampler2D;

// Stage inputs
layout (location = 0) in vec2 i_uv;

// Stage outputs
layout (location = 0 ) out vec3 o_color;

// Main
void main(void)
{
  o_color = texture(u_sampler2D, i_uv).rgb;
}
