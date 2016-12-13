#ifndef _WING_ENGINE_TEST_SHADER_H_
#define _WING_ENGINE_TEST_SHADER_H_

#include <string>

const std::string test_vs = "#version 330 core \
							layout(location = 0) in vec3 vertexPosition_modelspace;	\
							void main()  \
							{	\
								gl_Position.xyz = vertexPosition_modelspace;	\
								gl_Position.w = 1.0;	\
							}  \ ";


const std::string test_fs = "void main()	\
							{	\
								gl_FragColor = vec4(0.4, 0.4, 0.8, 1.0);	\
							}  \ ";

#endif