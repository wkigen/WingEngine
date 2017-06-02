#include "geometry_pass.h"
#include "renderer\renderer_system.h"
#include "shader\geometry_shader.h"

namespace WingEngine
{


	GeometryPass::GeometryPass()
	{

	}

	GeometryPass::~GeometryPass()
	{

	}

	void GeometryPass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = context->createProgram("geometry", geometry_vs, geometry_fs);

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mAttribColor = context->getAttribLocation(mProgram->getProgramID(), COLOR);
		mUniformModelMatrix = context->getUniformMatrix44fLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformMatrix44fLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
	}

	void GeometryPass::bind(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();

		mProgram->use();
		
		context->bindArrayBuffers(renderable->getVertixData().getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData().getGPUBufferId());
		
		DataElement* dataElement = renderable->getVertixData().getElement();
		context->enableVertexAttribArray(mAttribPosition);
		ElementFormat positionFormat = renderable->getVertixData().getElement()->getElementFormat(DataElementName::DataElementPosition);
		context->vertexAttribPointer(mAttribPosition, positionFormat.mSize, false, dataElement->getSize(), (void*)(positionFormat.mOffest*dataElement->getElementTypeSize()));

		context->enableVertexAttribArray(mAttribColor);
		ElementFormat colorFormat = renderable->getVertixData().getElement()->getElementFormat(DataElementName::DataElementColor);
		context->vertexAttribPointer(mAttribColor, colorFormat.mSize, false, dataElement->getSize(), (void*)(colorFormat.mOffest*dataElement->getElementTypeSize()));

		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44());
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44);
	}

	void GeometryPass::unBind()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
