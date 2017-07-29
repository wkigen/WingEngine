#include "base_pass.h"
#include "renderer\renderer_system.h"
#include "shader\base_shader.h"

namespace WingEngine
{


	BasePass::BasePass()
	{

	}

	BasePass::~BasePass()
	{

	}

	void BasePass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = context->createProgram("base", base_vs, base_fs);

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
	}

	void BasePass::bind(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();

		mProgram->use();
		context->enableVertexAttribArray(mAttribPosition);

		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());

		context->vertexAttribPointer(mAttribPosition, 3, false, renderable->getVertixData()->getElement()->getSize(), 0);

		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44());
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44);
	}

	void BasePass::unBind()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
