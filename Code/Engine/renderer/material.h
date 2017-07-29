#ifndef _WING_ENGINE_MATERIAL_H_
#define _WING_ENGINE_MATERIAL_H_

#include "common\engine_defines.h"
#include "base\object.h"
#include "texture.h"

using namespace WingCore;

namespace WingEngine
{

	class WING_ENGINE_API Material : public Object
	{
	public:
		Material();
		~Material();

		virtual void setTexture(Texture* texture) { mTexture = texture; }
		virtual Texture* getTexture() { return mTexture; }

	private:
		SmartPtr<Texture> mTexture;
	};


}


#endif // !_WING_ENGINE_CUBE_H_