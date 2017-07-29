#ifndef _WING_ENGINE_BASE_SHADER_H_
#define _WING_ENGINE_BASE_SHADER_H_

#include <string>

const std::string base_vs = "\
							attribute vec4 a_position;	\
							uniform mat4 u_projectViewMatrix;   \
							uniform mat4 u_modelViewMatrix;   \
							void main()  \
							{	\
								gl_Position = u_projectViewMatrix* u_modelViewMatrix *a_position ;    	\
							}  \ ";


const std::string base_fs = "void main()	\
							{	\
								gl_FragColor = vec4(0.4,0.4,0.8,1.0); 	\
							}  \ ";

#endif