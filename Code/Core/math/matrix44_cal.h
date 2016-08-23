#ifndef _IKAROS_MATRIX44_CAL_H_
#define _IKAROS_MATRIX44_CAL_H_

#include "point.h"
#include "matrix44.h"

namespace WingCore
{
	template<class T>
	inline Matrix44 mtxLookAt(Vector<T>& eye, Vector<T>& view, Vector<T>& up)
	{
		
		Vector<T> right = up.cross(view);

		right.normalize();

		up = view.cross(right);

		float m[4][4] = { 0 };
		m[0][0] = right[0];
		m[0][1] = up[0];
		m[0][2] = view[0];

		m[1][0] = right[1];
		m[1][1] = up[1];
		m[1][2] = view[1];

		m[2][0] = right[2];
		m[2][1] = up[2];
		m[2][2] = view[2];

		m[3][0] = -right.dot(eye);
		m[3][1] = -up.dot(eye);
		m[3][2] = -view.dot(eye);
		m[3][3] = 1.0f;

		return Matrix44(m);
	}


	template<class T>
	inline Matrix44 mtxLookAtLh(Point<T> eye, Point<T> at, Vector<T> up)
	{
		Vector<T> tmp = at - eye;
		tmp.normalize();

		Vector<T> eyev = eye - Point<T>(0, 0, 0);
		return mtxLookAt(eyev, tmp, up);
	}

	inline WING_CORE_API Matrix44 mtxProjectLh(float _fovy, float _aspect, float _near, float _far);

	inline WING_CORE_API Matrix44 mtxProjXYWH(float _x, float _y, float _width, float _height, float _near, float _far);
}

#endif