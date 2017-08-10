attribute vec4 a_position;
attribute vec4 a_normal;
attribute vec2 a_textureCoordinate;

uniform mat4 u_projectViewMatrix;
uniform mat4 u_modelViewMatrix;
uniform mat4 u_transposeInverseMatrix;

varying vec2 v_textureCoordinate;
varying vec4 v_worldPos;
varying vec3 v_normal;

void main()
{
    v_textureCoordinate = a_textureCoordinate;
    v_worldPos= u_modelViewMatrix * a_position;
    v_normal = vec3(normalize(u_transposeInverseMatrix * a_normal));

    gl_Position = u_projectViewMatrix* u_modelViewMatrix * a_position;
}