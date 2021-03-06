#ifndef _WING_ENGINE_TEST_SHADER_H_
#define _WING_ENGINE_TEST_SHADER_H_

#include <string>

const std::string test_vs = "\
							attribute vec4 a_position;	\
							uniform mat4 u_ProjectViewMatrix;   \
							uniform mat4 u_ModelViewMatrix;   \
							void main()  \
							{	\
								gl_Position = u_ProjectViewMatrix * u_ModelViewMatrix * a_position ;    	\
							}  \ ";


const std::string test_fs = "void main()	\
							{	\
								gl_FragColor = vec4(0.4,0.4,0.8,1.0); 	\
							}  \ ";

#endif