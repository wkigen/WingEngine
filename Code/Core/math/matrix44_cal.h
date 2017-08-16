#ifndef _IKAROS_MATRIX44_CAL_H_
#define _IKAROS_MATRIX44_CAL_H_

#include "point.h"
#include "matrix44.h"

namespace WingCore
{
	WING_CORE_API Matrix44 lhToRh(Matrix44& m);

	WING_CORE_API Matrix44 mtxLookAt(Vectorf& eye, Vectorf& view, Vectorf& up);

	WING_CORE_API Matrix44 mtxLookAtLh(Pointf eye, Pointf at, Vectorf up);

	WING_CORE_API Matrix44 mtxLookAtRh(Pointf eye, Pointf at, Vectorf up);

	WING_CORE_API Matrix44 mtxOrthoLh(real _width, real _height, real _nearPlane, real _farPlane);

	WING_CORE_API Matrix44 mtxOrthoRh(real _width, real _height, real _nearPlane, real _farPlane);

	WING_CORE_API Matrix44 mtxOrthLRBT(real _left, real _right, real _bottom, real _top, real _nearPlane, real _farPlane);

	WING_CORE_API Matrix44 mtxProjectLh(real _fovy, real _aspect, real _near, real _far);

	WING_CORE_API Matrix44 mtxProjectRh(real _fovy, real _aspect, real _near, real _far);

	WING_CORE_API Matrix44 mtxProjXYWH(real _x, real _y, real _width, real _height, real _near, real _far);
}

#endif