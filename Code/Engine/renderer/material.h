#ifndef _WING_ENGINE_MATERIAL_H_
#define _WING_ENGINE_MATERIAL_H_

#include "common\engine_defines.h"
#include "base\object.h"
#include "texture.h"
#include "math\vector.h"

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

		virtual void setAmbient(Vectorf ambient) { mAmbient = ambient; }
		virtual Vectorf getAmbient() { return mAmbient; }

		virtual void setDiffuse(Vectorf diffuse) { mDiffuse = diffuse; }
		virtual Vectorf getDiffuse() { return mDiffuse; }

		virtual void setSpecular(Vectorf specular) { mSpecular = specular; }
		virtual Vectorf getSpecluar() { return mSpecular; }

	private:
		SmartPtr<Texture> mTexture;
		
		Vectorf mAmbient;
		Vectorf mDiffuse;
		Vectorf mSpecular;
	};


}


#endif // !_WING_ENGINE_CUBE_H_