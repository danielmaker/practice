#ifdef GL_ES
precision mediump float;
#endif

vec2 u_Center = vec2(320.0, 180.0);
vec2 u_RectSize = vec2(200.0, 50.0);

vec4 u_FillColor = vec4(1.0, 1.0, 0.0, 1.0);
vec4 u_OutlineColor = vec4(0.0, 1.0, 0.0, 1.0);
float u_Radius = 4.0;
float u_LineHalfWidth = 1.5;

const float transitWidth = 1.0;

/// @param pt = gl_FragCoord.xy.
/// @param pos The center of the rounded frame.
/// @param size The inside box size of the rounded frame.
/// @param radius The radius of the corner. The distance between the inside box.
/// @return The distance between pt and the border.
///         A positive value means that the pt is outside the rounded rectangle.
///         A negative value means that the pt is inside the rounded rectangle.
///         Zero means that the pt is just on the border.
///
float distanceToRoundedBorder(vec2 pt, vec2 pos, vec2 size, float radius)
{
  vec2 diff = abs(pt - pos) - size;
  float distanceToInnerBox = (diff.x <= 0.0 && diff.y <= 0.0)
    ? max(diff.x, diff.y) // inside the box
    : length(max(abs(pt - pos), size) - size); // outside the box
  return distanceToInnerBox - radius;
}

void main(void)
{
  vec2 pt = gl_FragCoord.xy;

  // The fragment shader code draws a rounded rectangle. Basically, it can be broken down to:
  // 1. Define distance functions for the borders which define different areas.
  // 2. Calculate color intensity for each area.
  // 3. Calculate final color from area colors and their intensity.

  float distance = distanceToRoundedBorder(pt, u_Center, u_RectSize, u_Radius);

  float fadeOutside = 1.0 - smoothstep(u_LineHalfWidth, u_LineHalfWidth + transitWidth, distance);
  float fillIntensity = 1.0 - smoothstep(-(u_LineHalfWidth + transitWidth), -u_LineHalfWidth, distance);
  float outlineIntensity = (distance > 0.0) ? fadeOutside : (1.0 - fillIntensity);

  gl_FragColor = (u_OutlineColor * outlineIntensity)
               + (u_FillColor * fillIntensity);

  gl_FragColor.a *= fadeOutside;
}
