#include "geometry_texture_light_shadow_first_pass.h"
#include "renderer\renderer_system.h"
#include "shader\geometry_texture_light_shader.h"

namespace WingEngine
{


	GeometryTextureLightShadowFirstPass::GeometryTextureLightShadowFirstPass(uint32 width, uint32 height)
		:mWidth(width)
		,mHeight(height)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = RendererSystem::getInstance()->getProgram("shadow_map_first");
	}

	GeometryTextureLightShadowFirstPass::~GeometryTextureLightShadowFirstPass()
	{

	}

	void GeometryTextureLightShadowFirstPass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
		//mUniformViewPosition = context->getUniformLocation(mProgram->getProgramID(), VIEWPOSITION);
		mUniformLightNum = context->getUniformLocation(mProgram->getProgramID(), LIGHTNUM);
		//mUniformLightType = context->getUniformLocation(mProgram->getProgramID(), LIGHTTYPE);
		mUniformLightPosition = context->getUniformLocation(mProgram->getProgramID(), LIGHTPOSITION);
		mUniformLightMVPMatrix = context->getUniformLocation(mProgram->getProgramID(), LIGHTMVPMARTRIX);

		mColorTexture = WING_NEW Texture(mWidth, mHeight,TextureTypeRGB, TextureFormatRGB, ColorFormatRGB, DataElementReal);
		mColorTexture->bindGPUBuffer();
		mRenderTarget = WING_NEW RenderTarget(mColorTexture);
		mRenderTarget->setAttachmentPoint(AttachmentPointColor0);
		mRenderTarget->bindGPUBuffer();


		mDepthTexture = WING_NEW Texture(mWidth, mHeight, TextureTypeDepth, TextureFormatDepth, ColorFormatDepth, DataElementReal);
		mDepthTexture->bindGPUBuffer();
		mDepthRenderTarget = WING_NEW RenderTarget(mDepthTexture);
		mDepthRenderTarget->setAttachmentPoint(AttachmentPointDepth);
		mDepthRenderTarget->bindGPUBuffer();
	}

	void GeometryTextureLightShadowFirstPass::preRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mProgram->use();

		mLightType = (int32*)WING_ALLOC(sizeof(uint32)  * MAX_LIGHT);
		mLightPostion = (real*)WING_ALLOC(sizeof(real) * 3 * MAX_LIGHT);
		mLightDirection = (real*)WING_ALLOC(sizeof(real) * 3 * MAX_LIGHT);
		mLightColor = (real*)WING_ALLOC(sizeof(real) * 4 * MAX_LIGHT);
		mLightNum = RendererSystem::getInstance()->getLightsData(mLightType, mLightPostion, mLightDirection, mLightColor);

		context->setUniform1d(mUniformLightNum, mLightNum);
		//context->setUniform1dv(mUniformLightType, MAX_LIGHT, mLightType);
		context->setUniform3fv(mUniformLightPosition, MAX_LIGHT, mLightPostion);

		SmartPtr<Camera> camera = RendererSystem::getInstance()->getCamera();

		real lightMvpMatrix44[MAX_LIGHT * 16];

		int32 count = 0;
		for (uint32 ii = 0; ii < 3 * mLightNum; ii = ii + 3)
		{
			real posX = mLightPostion[ii];
			real posY = mLightPostion[ii + 1];
			real posZ = mLightPostion[ii + 2];

			real dirX = mLightDirection[ii];
			real dirY = mLightDirection[ii+1];
			real dirZ = mLightDirection[ii+2];

			Vectorf pos(posX, posY, posZ);
			Vectorf dir(dirX, dirY, dirZ);
			Vectorf up(0.0, 1.0, 0.0);

			Matrix44 lookat = mtxLookAt(pos, dir, up);
			SmartPtr<Light> light = RendererSystem::getInstance()->getLight(count);
			Matrix44 vp =  lookat * camera->getProjectMatrix44();
			memcpy(lightMvpMatrix44, vp.mData.data, 16 * sizeof(real));

			count++;
		}
		context->setUniformMatrix44f(mUniformLightMVPMatrix, MAX_LIGHT, lightMvpMatrix44);

		context->bindRenderTarget(mRenderTarget->getTargetId());
		context->clear();
	}

	void GeometryTextureLightShadowFirstPass::_render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getProjectViewMatrix44();
		Vectorf viewPosition = RendererSystem::getInstance()->getCamera()->getPosition();

		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());

		DataElement* dataElement = renderable->getVertixData()->getElement();
		//顶点
		context->enableVertexAttribArray(mAttribPosition);
		ElementFormat positionFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementPosition);
		context->vertexAttribPointer(mAttribPosition, positionFormat.mSize, false, dataElement->getSize(), (void*)(positionFormat.mOffest*dataElement->getElementTypeSize()));

		//世界矩阵 投影矩阵
		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44().mData.data);
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44.mData.data);

		//context->setUniform4f(mUniformViewPosition, viewPosition.x, viewPosition.y, viewPosition.z,1.0);
	}

	void GeometryTextureLightShadowFirstPass::render(Renderable* renderable)
	{
	
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());
	}

	void GeometryTextureLightShadowFirstPass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		context->bindRenderTarget(INVALID_BUFFERS);
		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
	}

}
