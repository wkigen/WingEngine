#include "geometry_texture_light_pass.h"
#include "renderer\renderer_system.h"
#include "shader\geometry_texture_light_shader.h"

namespace WingEngine
{


	GeometryTextureLightPass::GeometryTextureLightPass()
	{

	}

	GeometryTextureLightPass::~GeometryTextureLightPass()
	{

	}

	void GeometryTextureLightPass::init()
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
	}

	void GeometryTextureLightPass::bind(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();
		Vectorf viewPosition = RendererSystem::getInstance()->getCamera()->getPosition();

		context->enableDepth(true);

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

		Matrix44 transposeInverse = renderable->getModelViewMatrinx44();
		transposeInverse = transposeInverse.inverse();
		transposeInverse = transposeInverse.transpose();
		context->setUniformMatrix44f(mUniformTransposeInverseMatrix, 1, transposeInverse);

		context->setUniform3f(mUniformViewPosition, viewPosition.x, viewPosition.y, viewPosition.z);
	}

	void GeometryTextureLightPass::unBind()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->enableDepth(false);

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindTexture(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
