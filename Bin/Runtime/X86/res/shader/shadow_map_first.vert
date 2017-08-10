attribute vec4 a_position;

uniform mat4 u_modelViewMatrix;
uniform mat4 u_lightMVPMatrtix[5];

varying vec4 v_worldPos;


void main()
{
    v_worldPos = u_modelViewMatrix * a_position;

    gl_Position = u_lightMVPMatrtix[0] * u_modelViewMatrix * a_position;
}