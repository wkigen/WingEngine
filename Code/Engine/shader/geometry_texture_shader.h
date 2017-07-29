#ifndef _WING_ENGINE_GEOMETRY_TEXTURE_SHADER_H_
#define _WING_ENGINE_GEOMETRY_TEXTURE_SHADER_H_

#include <string>

const std::string geometry_texture_vs = "\
							attribute vec4 a_position;	\
							attribute vec2 a_textureCoordinate;	\
							uniform mat4 u_projectViewMatrix;   \
							uniform mat4 u_modelViewMatrix;   \
							varying vec2 v_textureCoordinate;	\
							void main()  \
							{	\
								v_textureCoordinate = a_textureCoordinate;	\
								gl_Position = u_projectViewMatrix* u_modelViewMatrix *a_position ;    	\
							}  \ ";


const std::string geometry_texture_fs = "\
							varying vec2 v_textureCoordinate;	\
							uniform sampler2D u_Texture; \
							void main()	\
							{	\
								gl_FragColor = texture2D(u_Texture, v_textureCoordinate); \
							}  \ ";

#endif