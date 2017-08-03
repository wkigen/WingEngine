#ifndef _WING_ENGINE_SHADER_H_
#define _WING_ENGINE_SHADER_H_

#define POSITION					"a_position"
#define NORMAL						"a_normal"
#define COLOR						"a_color"
#define TEXTIRECOORDINATE			"a_textureCoordinate"


#define VIEWPOSITION				"u_viewPosition"
#define TEXTURE						"u_texture"
#define PROJECTVIEWMARTIX			"u_projectViewMatrix"
#define MODELVIEWMARTIX				"u_modelViewMatrix"
#define PROJECTMODELVIEWMARTIX		"u_projectModelViewMatrix"
#define TRANSPOSEINVERSEMATRIX		"u_transposeInverseMatrix"

#define LIGHTNUM					"u_lightNum"
#define LIGHTTYPE					"u_lightType"
#define LIGHTPOSITION				"u_lightPosition"
#define LIGHTDIRECTION				"u_lightDirection"
#define LIGHTCOLOR					"u_lightColor"

#define SHINESS						"u_shiness"
#define AMBIENT						"u_ambient"
#define DIFFUSE						"u_diffuse"
#define SPECULAR					"u_specular"


#endif