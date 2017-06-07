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
		Camera(real _fovy, real _aspect, real _near, real _far,Pointf _eye, Pointf _view, Vectorf _up);
		~Camera();

		void		setCamera(real _fovy, real _aspect, real _near, real _far, Pointf _eye, Pointf _view, Vectorf _up);

		void		translation(const Vectorf &t);
		void		rotate(const Vectorf &t, const real angle);

		Matrix44	getmProjectModelMatrix44() {return mProjectModelMatrix44; }

	private:

		Matrix44 mProjectViewMatrix44,mProjectModelMatrix44;
	};
}

#endif