attribute vec4 a_position;

uniform mat4 u_projectViewMatrix;
uniform mat4 u_modelViewMatrix;
uniform mat4 u_viewPosition

varying float v_depth;

void main()
{
    vec4 worldPos = u_modelViewMatrix * a_position;
    v_depth = distance(u_viewPosition.xyz,worldPos.xyz);
    gl_Position = u_projectViewMatrix* u_modelViewMatrix * a_position;
}