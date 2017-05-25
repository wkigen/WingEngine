#ifndef _WING_ENGINE_TEST_SHADER_H_
#define _WING_ENGINE_TEST_SHADER_H_

#include <string>

const std::string test_vs = "uniform mat4 u_ProjectModelViewMatrix;   \
							void main()  \
							{	\
								gl_Position = u_ProjectModelViewMatrix * gl_Vertex ;    	\
							}  \ ";


const std::string test_fs = "void main()	\
							{	\
								gl_FragColor = vec4(0.4,0.4,0.8,1.0); 	\
							}  \ ";

#endif