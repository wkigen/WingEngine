#ifndef _WING_ENGINE_CAMERA_H_
#define _WING_ENGINE_CAMERA_H_


#include "common\engine_defines.h"
#include "math\matrix44_cal.h"

using namespace WingCore;

namespace WingEngine
{
	class WING_ENGINE_API Camera
	{

	public:
		Camera(float _fovy, float _aspect, float _near, float _far,Point<float> _eye, Point<float> _view, Vector<float> _up);
		~Camera();

		void		translation(const Vector<float> &t);
		void		rotate(const Vector<float> &t);

		Matrix44	getModelViewMatrinx44() { return mModelViewMatrix44; }
		Matrix44	getProjectViewMatrinx44() { return mProjectViewMatrix44; }
		Matrix44	getProjectModelMatrix44() { return mProjectModelMatrix44; }

	private:
		Point<float> mEye, mView;
		Vector<float> nUp;
		Matrix44 mModelViewMatrix44,mProjectViewMatrix44,mProjectModelMatrix44;
	};
}

#endif