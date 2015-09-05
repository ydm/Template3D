#version 450 core

uniform float u_zoom;
uniform vec2 u_center;

// Stage inputs
layout (location = 0) in vec3 i_vertex;
layout (location = 1) in vec3 i_color;

// Stage outputs
layout (location = 0 ) out vec3 o_color;

vec3 inv(const in vec3 v)
{
  return vec3(1.0) - v;
}

vec3 mandelbrot(const in vec2 frag, const in float zoom, const in vec2 center)
{
  float safeZoom = (zoom > 0.0) ? zoom : 1.0;
  const vec2 c = frag / safeZoom - center;
  vec2 z = c;
  vec3 color;

  for (float i = 0.0; i < 1.0; i += 0.001)
  {
    const float x = (z.x*z.x - z.y*z.y) + c.x;
    const float y = (2.0 * z.x * z.y)   + c.y;
    z.x = x;
    z.y = y;

    const float square = x*x + y*y;
    if (square > 4.0)
    {
      break;
    }

    // color = vec3(sin(i * 2.0), i, sin(i * 1.0));
    color = vec3(sin(i), i, sin(i * 2.0));
    // color = inv(vec3(i, i, i));
  }

  return color;
}

// Main
void main(void)
{
  // o_color = vec3(0.0, 0.0, 1.0);
  o_color = mandelbrot(i_vertex.xy, u_zoom, u_center);
}
