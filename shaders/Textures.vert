#version 450 core


// Uniforms
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;


// Stage inputs
layout (location = 0) in vec3 i_vertex;
layout (location = 1) in vec2 i_uv;

// Stage outputs
layout (location = 0) out vec2 o_uv;


// Main
void main(void)
{
  gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(i_vertex, 1.0);
  // o_uv = i_uv;
  o_uv = i_vertex.xy;
}
