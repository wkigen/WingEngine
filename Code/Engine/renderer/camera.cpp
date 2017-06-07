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
		Matrix44 lookatMatrix = mtxLookAtRh(_eye, _view, _up);
		mProjectViewMatrix44 = mtxProjectRh(_fovy, _aspect, _near, _far);
		mProjectModelMatrix44 = lookatMatrix * mProjectViewMatrix44 ;
	}


	void Camera::translation(const Vectorf &t)
	{
		Node::translation(t);
		mProjectModelMatrix44 = mModelMatrix44 * mProjectViewMatrix44 ;
	}

	void Camera::rotate(const Vectorf &t, const real angle)
	{
		Node::rotate(t,angle);
		mProjectModelMatrix44 = mModelMatrix44 * mProjectViewMatrix44 ;
	}
}