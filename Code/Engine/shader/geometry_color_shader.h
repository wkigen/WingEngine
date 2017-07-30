#ifndef _WING_ENGINE_GEOMETRY_COLOR_SHADER_H_
#define _WING_ENGINE_GEOMETRY_COLOR_SHADER_H_

#include <string>

const std::string geometry_color_vs = "\
							attribute vec4 a_position;	\
							attribute vec4 a_color;	\
							uniform mat4 u_projectViewMatrix;   \
							uniform mat4 u_modelViewMatrix;   \
							varying vec4 v_color;	\
							void main()  \
							{	\
								v_color = a_color;	\
								gl_Position = u_projectViewMatrix* u_modelViewMatrix *a_position ;    	\
							}  \ ";


const std::string geometry_color_fs = "\
							varying vec4 v_color;	\
							void main()	\
							{	\
								gl_FragColor = v_color; 	\
							}  \ ";

#endif