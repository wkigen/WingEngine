#ifndef _WING_ENGINE_COLOR_H_
#define _WING_ENGINE_COLOR_H_

#include "common\engine_defines.h"
#include "base\object.h"
#include "resource\image.h"

namespace WingEngine
{

	class WING_ENGINE_API Texture :public Object
	{

	public:
		Texture(Image* image);
		~Texture();

		virtual void bindGPUBuffer();
		virtual uint32 getGPUBufferId() { return mGPUBufferId; }

		virtual Image* getImage() { return mImage; };
		virtual void setImage(Image* image) { mImage = image; }

	private:
		Image* mImage;
		uint32 mGPUBufferId;
	};

}


#endif