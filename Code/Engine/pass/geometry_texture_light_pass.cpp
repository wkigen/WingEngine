#include "geometry_texture_light_pass.h"
#include "renderer\renderer_system.h"


namespace WingEngine
{


	GeometryTextureLightPass::GeometryTextureLightPass()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		mProgram = RendererSystem::getInstance()->getProgram("geometry_texture_light");

	}

	GeometryTextureLightPass::~GeometryTextureLightPass()
	{

	}

	void GeometryTextureLightPass::init()
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
	}

	void GeometryTextureLightPass::preRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		mProgram->use();

	}

	void GeometryTextureLightPass::_render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		Matrix44 projectMatrix44 = RendererSystem::getInstance()->getCamera()->getProjectViewMatrix44();
		Vectorf viewPosition = RendererSystem::getInstance()->getCamera()->getPosition();
		Material* material = renderable->getMaterial();

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

		context->setUniformMatrix44f(mUniformModelMatrix, 1, renderable->getModelViewMatrinx44().mData.data);
		context->setUniformMatrix44f(mUniformProjectdViewMatrix, 1, projectMatrix44.mData.data);

		Matrix44 inverseTranspose;
		renderable->getModelViewMatrinx44().inverse(inverseTranspose);
		inverseTranspose = inverseTranspose.transpose();
		context->setUniformMatrix44f(mUniformTransposeInverseMatrix, 1, inverseTranspose.mData.data);

		context->setUniform3f(mUniformViewPosition, viewPosition.x, viewPosition.y, viewPosition.z);

		context->setUniform3f(mUniformAmbient, material->getAmbient());
		context->setUniform3f(mUniformDiffuse, material->getDiffuse());
		context->setUniform3f(mUniformSpecular, material->getSpecluar());

	}

	void GeometryTextureLightPass::render(Renderable* renderable)
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();
		_render(renderable);
		context->draw(renderable->getIndeiceData()->getDataNum());

	}

	void GeometryTextureLightPass::postRender()
	{
		RendererContext* context = RendererSystem::getInstance()->getRendererContext();

		context->bindArrayBuffers(INVALID_BUFFERS);
		context->bindElementBuffers(INVALID_BUFFERS);
		context->bindTexture(INVALID_BUFFERS);
		context->disableVertexAttribArray();
	}

}
