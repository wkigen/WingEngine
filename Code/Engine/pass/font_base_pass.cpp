#include "font_Base_pass.h"
#include "renderer\renderer_system.h"

namespace WingEngine
{


	FontBasePass::FontBasePass()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = RendererSystem::getInstance()->getProgram("fontBasePass");
	}

	FontBasePass::~FontBasePass()
	{

	}

	void FontBasePass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mUniformOrthoViewMatrix = context->getUniformLocation(mProgram->getProgramID(), ORTHOVIEWMARTIX);
	}

	void FontBasePass::preRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mProgram->use();
	}

	void FontBasePass::_render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 orthoMatrix44 = RendererSystem::getInstance()->getCamera()->getOrthoViewMatrix44();

		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());

		context->enableVertexAttribArray(mAttribPosition);
		context->vertexAttribPointer(mAttribPosition, 3, false, renderable->getVertixData()->getElement()->getSize(), 0);

		DataElement* dataElement = renderable->getVertixData()->getElement();

		context->enableVertexAttribArray(mAttribPosition);
		ElementFormat positionFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementPosition);
		context->vertexAttribPointer(mAttribPosition, positionFormat.mSize, false, dataElement->getSize(), (void*)(positionFormat.mOffest*dataElement->getElementTypeSize()));

		context->bindTexture(renderable->getMaterial()->getTexture()->getGPUBufferId());

		context->enableVertexAttribArray(mAttribTextureCoordinate);
		ElementFormat textureFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementTexture);
		context->vertexAttribPointer(mAttribTextureCoordinate, textureFormat.mSize, false, dataElement->getSize(), (void*)(textureFormat.mOffest*dataElement->getElementTypeSize()));

		context->setUniformMatrix44f(mUniformOrthoViewMatrix, 1, orthoMatrix44.mData.data);
	}

	void FontBasePass::render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());
	}

	void FontBasePass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindTexture(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
