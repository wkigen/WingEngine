#include "geometry_color_pass.h"
#include "renderer\renderer_system.h"


namespace WingEngine
{


	GeometryColorPass::GeometryColorPass()
	{

	}

	GeometryColorPass::~GeometryColorPass()
	{

	}

	void GeometryColorPass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = RendererSystem::getInstance()->getProgram("geometry_color");

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mAttribColor = context->getAttribLocation(mProgram->getProgramID(), COLOR);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
	}

	void GeometryColorPass::preRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mProgram->use();

	}

	void GeometryColorPass::_render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();
		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());

		DataElement* dataElement = renderable->getVertixData()->getElement();

		context->enableVertexAttribArray(mAttribPosition);
		ElementFormat positionFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementPosition);
		context->vertexAttribPointer(mAttribPosition, positionFormat.mSize, false, dataElement->getSize(), (void*)(positionFormat.mOffest*dataElement->getElementTypeSize()));

		context->enableVertexAttribArray(mAttribColor);
		ElementFormat colorFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementColor);
		context->vertexAttribPointer(mAttribColor, colorFormat.mSize, false, dataElement->getSize(), (void*)(colorFormat.mOffest*dataElement->getElementTypeSize()));

		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44());
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44);

		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());
	}
	

	void GeometryColorPass::render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());
	}

	void GeometryColorPass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindTexture(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
