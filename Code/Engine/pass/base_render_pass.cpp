#include "base_render_pass.h"
#include "renderer\renderer_system.h"

namespace WingEngine
{


	BaseRenderPass::BaseRenderPass()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = RendererSystem::getInstance()->getProgram("base_render");
	}

	BaseRenderPass::~BaseRenderPass()
	{

	}

	void BaseRenderPass::init()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mAttribPosition = context->getAttribLocation(mProgram->getProgramID(), POSITION);
		mAttribNormal = context->getAttribLocation(mProgram->getProgramID(), NORMAL);
		mAttribTextureCoordinate = context->getAttribLocation(mProgram->getProgramID(), TEXTIRECOORDINATE);
		mUniformTexture = context->getUniformLocation(mProgram->getProgramID(), TEXTURE0);
		mUniformModelMatrix = context->getUniformLocation(mProgram->getProgramID(), MODELVIEWMARTIX);
		mUniformProjectdViewMatrix = context->getUniformLocation(mProgram->getProgramID(), PROJECTVIEWMARTIX);
		mUniformTransposeInverseMatrix = context->getUniformLocation(mProgram->getProgramID(), TRANSPOSEINVERSEMATRIX);
		mUniformViewPosition = context->getUniformLocation(mProgram->getProgramID(), VIEWPOSITION);
		mUniformShiness = context->getUniformLocation(mProgram->getProgramID(), SHINESS);
		mUniformAmbient = context->getUniformLocation(mProgram->getProgramID(), AMBIENT);
		mUniformDiffuse = context->getUniformLocation(mProgram->getProgramID(), DIFFUSE);
		mUniformSpecular = context->getUniformLocation(mProgram->getProgramID(), SPECULAR);
		mUniformLightNum = context->getUniformLocation(mProgram->getProgramID(), LIGHTNUM);
		mUniformLightType = context->getUniformLocation(mProgram->getProgramID(), LIGHTTYPE);
		mUniformLightPosition = context->getUniformLocation(mProgram->getProgramID(), LIGHTPOSITION);
		mUniformLightDirection = context->getUniformLocation(mProgram->getProgramID(), LIGHTDIRECTION);
		mUniformLightColor= context->getUniformLocation(mProgram->getProgramID(), LIGHTCOLOR);
	}

	void BaseRenderPass::preRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mProgram->use();

		mLightType = (int32*)WING_ALLOC(sizeof(uint32)  * MAX_LIGHT);
		mLightPostion = (real*)WING_ALLOC(sizeof(real) * 3 * MAX_LIGHT);
		mLightDirection = (real*)WING_ALLOC(sizeof(real) * 3 * MAX_LIGHT);
		mLightColor = (real*)WING_ALLOC(sizeof(real) * 4 * MAX_LIGHT);
		mShiness = (real*)WING_ALLOC(sizeof(real) * MAX_LIGHT);
		mLightNum = RendererSystem::getInstance()->getLightsData(mLightType, mLightPostion, mLightDirection, mLightColor, mShiness);

		context->setUniform1d(mUniformLightNum, mLightNum);
		context->setUniform1dv(mUniformLightType, MAX_LIGHT, mLightType);
		context->setUniform3fv(mUniformLightPosition, MAX_LIGHT, mLightPostion);
		context->setUniform3fv(mUniformLightDirection, MAX_LIGHT, mLightDirection);
		context->setUniform4fv(mUniformLightColor, MAX_LIGHT, mLightColor);
		context->setUniform1fv(mUniformShiness, MAX_LIGHT, mShiness);

	}

	void BaseRenderPass::_render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getProjectViewMatrix44();
		Vectorf viewPosition = RendererSystem::getInstance()->getCamera()->getPosition();
		Material* material = renderable->getMaterial();

		context->bindArrayBuffers(renderable->getVertixData()->getGPUBufferId());
		context->bindElementBuffers(renderable->getIndeiceData()->getGPUBufferId());

		DataElement* dataElement = renderable->getVertixData()->getElement();

		//顶点
		context->enableVertexAttribArray(mAttribPosition);
		ElementFormat positionFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementPosition);
		context->vertexAttribPointer(mAttribPosition, positionFormat.mSize, false, dataElement->getSize(), (void*)(positionFormat.mOffest*dataElement->getElementTypeSize()));

		//法线
		context->enableVertexAttribArray(mAttribNormal);
		ElementFormat normalFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementNormal);
		context->vertexAttribPointer(mAttribNormal, normalFormat.mSize, false, dataElement->getSize(), (void*)(normalFormat.mOffest*dataElement->getElementTypeSize()));

		//纹理
		context->bindTexture(renderable->getMaterial()->getTexture()->getGPUBufferId());

		context->enableVertexAttribArray(mAttribTextureCoordinate);
		ElementFormat textureFormat = renderable->getVertixData()->getElement()->getElementFormat(DataElementName::DataElementTexture);
		context->vertexAttribPointer(mAttribTextureCoordinate, textureFormat.mSize, false, dataElement->getSize(), (void*)(textureFormat.mOffest*dataElement->getElementTypeSize()));

		//世界矩阵 投影矩阵
		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44().mData.data);
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44.mData.data);

		Matrix44 inverseTranspose;
		renderable->getModelViewMatrinx44().inverse(inverseTranspose);
		inverseTranspose = inverseTranspose.transpose();
		context->setUniformMatrix44f(mUniformTransposeInverseMatrix, 1, inverseTranspose.mData.data);

		context->setUniform3f(mUniformViewPosition, viewPosition);

		context->setUniform3f(mUniformAmbient, material->getAmbient());
		context->setUniform3f(mUniformDiffuse, material->getDiffuse());
		context->setUniform3f(mUniformSpecular, material->getSpecluar());
	}

	void BaseRenderPass::render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());

	}

	void BaseRenderPass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindTexture(INVALID_BUFFERS);
		context->disableVertexAttribArray();

		WING_FREE(mLightType);
		WING_FREE(mLightPostion);
		WING_FREE(mLightDirection);
		WING_FREE(mLightColor);
	}

}
