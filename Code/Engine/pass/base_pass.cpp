#include "base_pass.h"
#include "renderer\renderer_system.h"
#include "shader\base_shader.h"

namespace WingEngine
{


	BasePass::BasePass(Renderable* renderable)
		:RenderPass(renderable)
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
		mUniformModelMatrix = context->getUniformMatrix44fLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformMatrix44fLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
	}

	void BasePass::bind() 
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getmProjectModelMatrix44();

		mProgram->use();
		context->enableVertexAttribArray(mAttribPosition);

		context->bindArrayBuffers(mRenderable->getVertixData().getGPUBufferId());
		context->bindElementBuffers(mRenderable->getIndeiceData().getGPUBufferId());

		context->vertexAttribPointer(mAttribPosition, mRenderable->getVertixData().getDataSize(), false, mRenderable->getVertixData().getElementSize(), 0);

		context->setUniformMatrix44f(mUniformModelMatrix, 1, mRenderable->getModelViewMatrinx44());
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
