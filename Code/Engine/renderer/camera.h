#ifndef _WING_ENGINE_CAMERA_H_
#define _WING_ENGINE_CAMERA_H_


#include "common\engine_defines.h"
#include "scene\node.h"


namespace WingEngine
{
	class WING_ENGINE_API Camera : public Node
	{

	public:
		Camera() {};
		Camera(real _width, real _height, real _fovy, real _aspect, real _near, real _far,Pointf _eye, Pointf _view, Vectorf _up);
		~Camera();

		void		setCamera(real _width,real _height,real _fovy, real _aspect, real _near, real _far, Pointf _eye, Pointf _view, Vectorf _up);

		virtual void translation(const Vectorf &t);
		virtual void rotate(const Vectorf &t, const real angle);

		Matrix44	getProjectMatrix44() {return mProjectMatrix44; }

		Matrix44	getOrthoMatrix44() { return mOrthoMatrix44; }

		Matrix44	getProjectViewMatrix44() {return mProjectViewMatrix44;}

		Matrix44	getOrthoViewMatrix44() { return mOrthoViewMatrix44; }

		virtual Pointf getEye() { return mEye; }

	protected:
		real mWidth;
		real mHeight;
		Pointf mEye;
		Pointf mView;
		Vectorf mUp;
		Matrix44 mProjectViewMatrix44,mProjectMatrix44;
		Matrix44 mOrthoMatrix44, mOrthoViewMatrix44;
	};
}

#endif