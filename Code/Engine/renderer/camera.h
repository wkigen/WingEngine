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
		Camera(Point<float> _eye, Point<float> _view, Vector<float> _up);
		~Camera();

		void translation(const Vector<float> &t);

	private:
		Point<float> mEye, mView;
		Vector<float> nUp;
		Matrix44 mMatrix44;
	};
}

#endif