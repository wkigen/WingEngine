#include "camera.h"

namespace WingEngine
{
	Camera::Camera(real _fovy, real _aspect, real _near, real _far, Pointf _eye, Pointf _view, Vectorf _up)
	{
		setCamera(_fovy, _aspect, _near, _far, _eye, _view, _up);
		mPosition = Vectorf(_view.x, _view.y,_view.z);
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
		mProjectViewMatrix44 = mtxProjectRh(_fovy, _aspect, _near, _far);
		mProjectModelMatrix44 = lookatMatrix * mProjectViewMatrix44 ;
		mPosition = Vectorf(_eye.x, _eye.y, _eye.z);
	}

	void Camera::positionToEye()
	{
		mEye.x = mPosition.x;
		mEye.y = mPosition.y;
		mEye.z = mPosition.z;
	}

	void Camera::translation(const Vectorf &t)
	{
		Node::translation(t);
		positionToEye();
		Matrix44 lookatMatrix = mtxLookAtRh(mEye, mView, mUp);
		mProjectModelMatrix44 = mModelMatrix44 * lookatMatrix * mProjectViewMatrix44 ;
	}

	void Camera::rotate(const Vectorf &t, const real angle)
	{
		Node::rotate(t,angle);
		positionToEye();
		Matrix44 lookatMatrix = mtxLookAtRh(mEye, mView, mUp);
		mProjectModelMatrix44 = mModelMatrix44 * lookatMatrix * mProjectViewMatrix44 ;
	}
}