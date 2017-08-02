#include "geometry_texture_light_shadow_pass.h"
#include "renderer\renderer_system.h"
#include "shader\geometry_texture_light_shader.h"

namespace WingEngine
{


	GeometryTextureLightShadowPass::GeometryTextureLightShadowPass(uint32 width, uint32 height)
		:mWidth(width)
		,mHeight(height)
	{

	}

	GeometryTextureLightShadowPass::~GeometryTextureLightShadowPass()
	{

	}

	void GeometryTextureLightShadowPass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = context->createProgram("geometry_texture_light", geometry_texture_light_vs, geometry_texture_light_fs);

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mAttribNormal = context->getAttribLocation(mProgram->getProgramID(), NORMAL);
		mAttribTextureCoordinate = context->getAttribLocation(mProgram->getProgramID(), TEXTIRECOORDINATE);
		mUniformTexture = context->getUniformLocation(mProgram->getProgramID(), TEXTURE);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
		mUniformTransposeInverseMatrix = context->getUniformLocation(mProgram->getProgramID(), TRANSPOSEINVERSEMATRIX);
		mUniformViewPosition = context->getUniformLocation(mProgram->getProgramID(), VIEWPOSITION);
		mUniformShiness = context->getUniformLocation(mProgram->getProgramID(), SHINESS);
		mUniformAmbient = context->getUniformLocation(mProgram->getProgramID(), AMBIENT);
		mUniformDiffuse = context->getUniformLocation(mProgram->getProgramID(), DIFFUSE);
		mUniformSpecular = context->getUniformLocation(mProgram->getProgramID(), SPECULAR);

		mTexture = WING_NEW Texture(mWidth, mHeight,TextureTypeRGB, TextureFormatRGB, ColorFormatRGB, DataElementUByte);
		mTexture->bindGPUBuffer();
		mRenderTarget = WING_NEW RenderTarget(mTexture);
		mRenderTarget->setAttachmentPoint(AttachmentPointColor0);
		mRenderTarget->bindGPUBuffer();

		mDepthTexture = WING_NEW Texture(mWidth, mHeight, TextureTypeDepth, TextureFormatDepth, ColorFormatDepth, DataElementUInt);
		mDepthTexture->bindGPUBuffer();
		mDepthRenderTarget = WING_NEW RenderTarget(mDepthTexture);
		mDepthRenderTarget->setAttachmentPoint(AttachmentPointDepth);
		mDepthRenderTarget->bindGPUBuffer();
	}

	void GeometryTextureLightShadowPass::preRender(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();
		Vectorf viewPosition = RendererSystem::getInstance()->getCamera()->getPosition();
		Material* material = renderable->getMaterial();

		mProgram->use();
		
		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());
		
		DataElement* dataElement = renderable->getVertixData()->getElement();

		context->enableVertexAttribArray(mAttribPosition);
		ElementFormat positionFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementPosition);
		context->vertexAttribPointer(mAttribPosition, positionFormat.mSize, false, dataElement->getSize(), (void*)(positionFormat.mOffest*dataElement->getElementTypeSize()));

		context->enableVertexAttribArray(mAttribNormal);
		ElementFormat normalFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementNormal);
		context->vertexAttribPointer(mAttribNormal, normalFormat.mSize, false, dataElement->getSize(), (void*)(normalFormat.mOffest*dataElement->getElementTypeSize()));

		context->bindTexture(renderable->getMaterial()->getTexture()->getGPUBufferId());
		context->enableVertexAttribArray(mAttribTextureCoordinate);
		ElementFormat textureFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementTexture);
		context->vertexAttribPointer(mAttribTextureCoordinate, textureFormat.mSize, false, dataElement->getSize(), (void*)(textureFormat.mOffest*dataElement->getElementTypeSize()));

		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44());
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44);

		Matrix44 inverseTranspose;
		renderable->getModelViewMatrinx44().inverse(inverseTranspose);
		inverseTranspose = inverseTranspose.transpose();
		context->setUniformMatrix44f(mUniformTransposeInverseMatrix, 1, inverseTranspose);

		context->setUniform3f(mUniformViewPosition, viewPosition.x, viewPosition.y, viewPosition.z);

		context->setUniform1f(mUniformShiness, material->getShiness());
		context->setUniform3f(mUniformAmbient, material->getAmbient());
		context->setUniform3f(mUniformDiffuse, material->getDiffuse());
		context->setUniform3f(mUniformSpecular, material->getSpecluar());

	}

	void GeometryTextureLightShadowPass::render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindRenderTarget(mRenderTarget->getTargetId());
		context->clear();
		BasePass::render(renderable);
	
		context->bindRenderTarget(INVALID_BUFFERS);
		context->bindTexture(mTexture->getGPUBufferId());
		BasePass::render(renderable);
	}

	void GeometryTextureLightShadowPass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindTexture(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
