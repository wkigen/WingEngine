#include "matrix44_cal.h"


namespace WingCore
{
	Matrix44 lhToRh(Matrix44& mat)
	{
		mat.mData.data[8] = -mat.mData.data[8];
		mat.mData.data[9] = -mat.mData.data[9];
		mat.mData.data[10] = -mat.mData.data[10];
		mat.mData.data[11] = -mat.mData.data[11];
		return mat;
	}

	Matrix44 mtxLookAt(Vectorf& eye, Vectorf& view, Vectorf& up)
	{

		Vectorf right = up.cross(view);
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

	Matrix44 mtxLookAtLh(Pointf eye, Pointf at, Vectorf up)
	{
		Vectorf tmp = at - eye;
		tmp.normalize();

		Vectorf eyev = eye - Pointf(0, 0, 0);
		return mtxLookAt(eyev, tmp, up);
	}

	Matrix44 mtxLookAtRh(Pointf eye, Pointf at, Vectorf up)
	{
		Vectorf tmp = eye - at;
		tmp.normalize();

		Vectorf eyev = eye - Pointf(0, 0, 0);
		return mtxLookAt(eyev, tmp, up);
	}

	Matrix44 mtxOrthoLh(real _width, real _height, real _nearPlane, real _farPlane)
	{
		real w_2(_width / 2);
		real h_2(_height / 2);
		return mtxOrthLRBT(-w_2, w_2, -h_2, h_2, _nearPlane, _farPlane);
	}

	Matrix44 mtxOrthoRh(real _width, real _height, real _nearPlane, real _farPlane)
	{
		return lhToRh(mtxOrthoLh(_width, _height, _nearPlane, _farPlane));
	}

	Matrix44 mtxOrthLRBT(real _left, real _right, real _bottom, real _top,real _nearPlane, real _farPlane)
	{
		real q(real(1) / (_farPlane - _nearPlane));
		real invWidth(real(1) / (_right - _left));
		real invHeight(real(1) / (_top - _bottom));

		float m[4][4] = { 0 };
		m[0][0] = invWidth + invWidth;
		m[1][1] = invHeight + invHeight;
		m[2][2] = q;
		m[3][0] = -(_left + _right) * invWidth;
		m[3][1] = -(_top + _bottom) * invHeight;
		m[3][2] = -_nearPlane * q;
		m[3][3] = 1;

		return Matrix44(m);
	}

	Matrix44 mtxProjectLh(real _fovy, real _aspect, real _near, real _far)
	{
		const real height = 1.0f / Math<real>::tan(Math<real>::toRad(_fovy)*0.5f);
		const real width = height * 1.0f / _aspect;
		return mtxProjXYWH(0.0f, 0.0f, width, height, _near, _far);
	}
	
	Matrix44 mtxProjectRh(real _fovy, real _aspect, real _near, real _far)
	{
		const real height = 1.0f / Math<real>::tan(Math<real>::toRad(_fovy)*0.5f);
		const real width = height * 1.0f / _aspect;
		Matrix44 m = mtxProjXYWH(0.0f, 0.0f, width, height, _near, _far);

		return lhToRh(m);
	}

	Matrix44 mtxProjXYWH(real _x, real _y, real _width, real _height, real _near, real _far)
	{
		const real diff = _far - _near;
		const real aa =  _far / diff;
		const real bb =  _near * aa;

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