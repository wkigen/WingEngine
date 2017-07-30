#include "geometry_color_pass.h"
#include "renderer\renderer_system.h"
#include "shader\geometry_color_shader.h"

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
		mProgram = context->createProgram("geometry_color", geometry_color_vs, geometry_color_fs);

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mAttribColor = context->getAttribLocation(mProgram->getProgramID(), COLOR);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
	}

	void GeometryColorPass::bind(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();

		context->enableDepth(true);

		mProgram->use();
		
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
	}

	void GeometryColorPass::unBind()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->enableDepth(false);

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindTexture(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
