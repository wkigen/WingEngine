#include "geometry_texture_pass.h"
#include "renderer\renderer_system.h"
#include "shader\geometry_texture_shader.h"

namespace WingEngine
{


	GeometryTexturePass::GeometryTexturePass()
	{

	}

	GeometryTexturePass::~GeometryTexturePass()
	{

	}

	void GeometryTexturePass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = context->createProgram("geometry_texture", geometry_texture_vs, geometry_texture_fs);

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mAttribTextureCoordinate = context->getAttribLocation(mProgram->getProgramID(), TEXTIRECOORDINATE);
		mUniformTexture = context->getUniformLocation(mProgram->getProgramID(), TEXTURE);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
	}

	void GeometryTexturePass::preRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mProgram->use();

	}

	void GeometryTexturePass::render(Renderable* renderable)
	{

		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();

		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());

		DataElement* dataElement = renderable->getVertixData()->getElement();
		context->enableVertexAttribArray(mAttribPosition);
		ElementFormat positionFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementPosition);
		context->vertexAttribPointer(mAttribPosition, positionFormat.mSize, false, dataElement->getSize(), (void*)(positionFormat.mOffest*dataElement->getElementTypeSize()));

		context->bindTexture(renderable->getMaterial()->getTexture()->getGPUBufferId());
		context->enableVertexAttribArray(mAttribTextureCoordinate);
		ElementFormat textureFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementTexture);
		context->vertexAttribPointer(mAttribTextureCoordinate, textureFormat.mSize, false, dataElement->getSize(), (void*)(textureFormat.mOffest*dataElement->getElementTypeSize()));

		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44());
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44);

		context->draw(renderable->getIndeiceData()->getDataNum());
	}

	void GeometryTexturePass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindTexture(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
