#ifndef _WING_ENGINE_TEST_SHADER_H_
#define _WING_ENGINE_TEST_SHADER_H_

#include <string>

const std::string test_vs = "   \
							void main()  \
							{	\
								gl_Position =ftransform();    	\
							}  \ ";


const std::string test_fs = "void main()	\
							{	\
								gl_FragColor =vec4(0.4,0.4,0.8,1.0); 	\
							}  \ ";

#endif