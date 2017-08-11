#include "base_pass.h"
#include "renderer\renderer_system.h"

namespace WingEngine
{


	BasePass::BasePass()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = RendererSystem::getInstance()->getProgram("base");
	}

	BasePass::~BasePass()
	{

	}

	void BasePass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
	}

	void BasePass::preRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		
		mProgram->use();

	}

	void BasePass::_render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getProjectViewMatrix44();

		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());

		context->enableVertexAttribArray(mAttribPosition);
		context->vertexAttribPointer(mAttribPosition, 3, false, renderable->getVertixData()->getElement()->getSize(), 0);

		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44().mData.data);
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44.mData.data);
	}

	void BasePass::render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());
	}

	void BasePass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
