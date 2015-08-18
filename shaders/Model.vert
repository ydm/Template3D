#version 450 core


// Uniforms
uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;


// Stage inputs
layout (location = 0) in vec3 i_vertex;
layout (location = 1) in vec3 i_normal;

// Stage outputs
layout (location = 0) out vec3 o_vertex;
layout (location = 1) out vec3 o_normal;


// Main
void main(void)
{
  gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(i_vertex, 1.0);

  o_vertex = i_vertex;
  o_normal = i_normal;
}
