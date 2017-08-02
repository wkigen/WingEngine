#ifndef _WING_ENGINE_RENDER_TARGET_H_
#define _WING_ENGINE_RENDER_TARGET_H_


#include "common\defines.h"
#include "common\engine_defines.h"
#include "texture.h"
#include "base\object.h"

namespace WingEngine
{
	class WING_ENGINE_API RenderTarget:public Object
	{

	public:

		RenderTarget();
		RenderTarget(Texture* texture);
		~RenderTarget();

		virtual void bindGPUBuffer();
		uint32 getTargetId() { return mTargetId; }

		virtual void setAttachmentPoint(AttachmentPoint attachmentPoint) { mAttachmentPoint = attachmentPoint; }
		virtual AttachmentPoint getAttachmentPoint() { return mAttachmentPoint; }

		virtual Texture* getTexture() { return mTexture; }
		virtual void setTexture(Texture* texture) { mTexture = texture; }

	protected:
		AttachmentPoint		mAttachmentPoint;
		SmartPtr<Texture>	mTexture;
		uint32				mTargetId;
	
	};

}


#endif