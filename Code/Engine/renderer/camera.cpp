#include "camera.h"

namespace WingEngine
{
	Camera::Camera(float _fovy, float _aspect, float _near, float _far, Point<float> _eye, Point<float> _view, Vector<float> _up)
	{
		mEye = _eye;
		mView = _view;
		nUp = _up;

		mProjectViewMatrix44 = mtxProjectLh(_fovy, _aspect, _near, _far);
		mModelViewMatrix44 = mtxLookAtLh(mEye, mView, nUp);
		mProjectModelMatrix44 = mProjectViewMatrix44 * mModelViewMatrix44;
	}


	Camera::~Camera()
	{

	}


	void Camera::translation(const Vector<float> &t)
	{
		Matrix44 traMatrix44;
		traMatrix44.setTranslation(t);
		mModelViewMatrix44 *= traMatrix44;

		mProjectModelMatrix44 = mProjectViewMatrix44 * mModelViewMatrix44;
	}

	void Camera::rotate(const Vector<float> &t)
	{
		mModelViewMatrix44.rotate(t);

		mProjectModelMatrix44 = mProjectViewMatrix44 * mModelViewMatrix44;
	}
}