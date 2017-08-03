#ifndef _WING_ENGINE_GEOMETRY_TEXTURE_SHADER_H_
#define _WING_ENGINE_GEOMETRY_TEXTURE_SHADER_H_

#include <string>

const std::string geometry_texture_light_vs = "\
							attribute vec4 a_position;	\
							attribute vec4 a_normal;	\
							attribute vec2 a_textureCoordinate;	\
							uniform mat4 u_projectViewMatrix;   \
							uniform mat4 u_modelViewMatrix;   \
							uniform mat4 u_transposeInverseMatrix;   \
							uniform vec3 u_viewPosition;	\
							varying vec2 v_textureCoordinate;	\
							varying vec3 v_position;	\
							varying vec3 v_normal;	\
							varying vec3 lightdir;	\
							varying vec3 halfvec;	\
							void main()  \
							{	\
								vec3 lightPos = vec3(5.0,5.0,0.0);	\
								gl_Position = u_projectViewMatrix* u_modelViewMatrix * a_position ;    	\
								v_textureCoordinate = a_textureCoordinate;	\
								vec4 pos = u_modelViewMatrix * a_position ;  \
								pos = pos / pos.w; \
								lightdir = normalize(lightPos - pos.xyz);	\
								vec3 eyedir = normalize(u_viewPosition - pos.xyz);	\
								halfvec = normalize(lightdir + eyedir);	\
								v_normal = vec3(normalize(u_transposeInverseMatrix * a_normal));	\
							}  \ ";


const std::string geometry_texture_light_fs = "\
							uniform sampler2D u_texture; \
							uniform float u_shiness; \
							uniform vec3 u_ambient; \
							uniform vec3 u_diffuse; \
							uniform vec3 u_specular; \
							varying vec3 v_normal;	\
							varying vec3 lightdir;	\
							varying vec3 halfvec;	\
							varying vec2 v_textureCoordinate;	\
							float amb = 0.3;	\
							float diff = 0.4;	\
							float spec = 0.3;	\
							void main()	\
							{	\
								vec3 color = texture2D(u_texture, v_textureCoordinate).rgb;  \
								vec3 lightdirN = normalize(lightdir);	\
								vec3 normalN = normalize(v_normal);	\
								float diffusefract = max(dot(lightdirN, normalN), 0.0);	\
								float specularfract = 0.0;	\
								if (diffusefract > 0.0) {	\
									vec3 halfvecN = normalize(halfvec);	\
									specularfract = max(dot(halfvecN, normalN), 0.0);	\
									specularfract = pow(specularfract, u_shiness);	\
								}	\
								gl_FragColor = vec4(amb * color * u_ambient+ diff * color * diffusefract *u_diffuse + spec * color * specularfract * u_specular, 1.0);	\
							}  \ ";

#endif