#include "camera.h"

namespace WingEngine
{
	Camera::Camera(real _fovy, real _aspect, real _near, real _far, Pointf _eye, Pointf _view, Vectorf _up)
	{
		setCamera(_fovy, _aspect, _near, _far, _eye, _view, _up);
	}


	Camera::~Camera()
	{

	}

	void Camera::setCamera(real _fovy, real _aspect, real _near, real _far, Pointf _eye, Pointf _view, Vectorf _up)
	{
		mEye = _eye;
		mView = _view;
		mUp = _up;

		Matrix44 lookatMatrix = mtxLookAtRh(_eye, _view, _up);
		mProjectMatrix44 = mtxProjectRh(_fovy, _aspect, _near, _far);
		mProjectViewMatrix44 = lookatMatrix * mProjectMatrix44;
		
	}

	void Camera::translation(const Vectorf &t)
	{
		int fff = 0;
		//todo
	}

	void Camera::rotate(const Vectorf &t, const real angle)
	{
		int fff = 0;
		//todo
	}
}