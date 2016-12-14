#include "camera.h"

namespace WingEngine
{
	Camera::Camera(Point<float> _eye, Point<float> _view, Vector<float> _up)
	{
		mEye = _eye;
		mView = _view;
		nUp = _up;

		mMatrix44 = mtxLookAtLh(mEye, mView, nUp);
	}


	Camera::~Camera()
	{

	}


	void Camera::translation(const Vector<float> &t)
	{
		mMatrix44.setTranslation(t);
	}

}