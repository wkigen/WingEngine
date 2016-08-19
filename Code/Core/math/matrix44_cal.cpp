#include "matrix44_cal.h"


namespace WingCore
{
	inline Matrix44 mtxProjectLh(float _fovy, float _aspect, float _near, float _far)
	{
		const float height = 1.0f / Math<float>::tan(Math<float>::toRad(_fovy)*0.5f);
		const float width = height * 1.0f / _aspect;
		return mtxProjXYWH(0.0f, 0.0f, width, height, _near, _far);
	}

	inline Matrix44 mtxProjXYWH(float _x, float _y, float _width, float _height, float _near, float _far)
	{
		const float diff = _far - _near;
		const float aa =  _far / diff;
		const float bb =  _near*aa;

		float m[4][4] = { 0 };

		m[0][0] = _width;
		m[1][1] = _height;
		m[2][0] =  -_x;
		m[2][1] =  -_y;
		m[2][2] =  aa;
		m[2][3] = 1.0f;
		m[3][2] = -bb;

		return Matrix44(m);
	}
	
}