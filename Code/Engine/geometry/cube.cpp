#include "cube.h"
#include "pass\geometry_pass.h"

namespace WingEngine
{

	real static_data[] = 
	{
		-1.0,-1.0,1.0,   0.0,0.0,0.0,  0.0,0.0,  1.0,0.0,0.0,1.0,
		1.0,-1.0,1.0,   0.0,0.0,0.0,  1.0,0.0,  1.0,0.0,0.0,1.0,
		1.0,1.0,1.0,   0.0,0.0,0.0,  1.0,1.0,  1.0,0.0,0.0,1.0,
		-1.0,1.0,1.0,   0.0,0.0,0.0,  0.0,1.0,  1.0,0.0,0.0,1.0,

		-1.0,-1.0,-1.0,   0.0,0.0,0.0,  0.0,0.0,  0.0,0.0,1.0,1.0,
		1.0,-1.0,-1.0,   0.0,0.0,0.0,  1.0,0.0,  0.0,0.0,1.0,1.0,
		1.0,1.0,-1.0,   0.0,0.0,0.0,  1.0,1.0,  0.0,0.0,1.0,1.0,
		-1.0,1.0,-1.0,   0.0,0.0,0.0,  0.0,1.0,  0.0,0.0,1.0,1.0,
	};

	uint32 static_indice[]=
	{
		0,1,3,
		1,2,3,

		1,5,2,
		5,6,2,

		2,6,3,
		6,7,3,

		4,0,7,
		0,3,7,

		5,1,4,
		1,0,4,

		4,5,7,
		5,6,7,
	};

	Cube::Cube()
	{
		mRenderType = RenderTypeGeometry;

		VertixData* vData = WING_NEW VertixData();
		DataElement* vElement = WING_NEW DataElement(DataElementType::DataElementReal,12);
		vElement->addElementFromat(DataElementName::DataElementPosition, 3, 0);
		vElement->addElementFromat(DataElementName::DataElementNormal, 3, 3);
		vElement->addElementFromat(DataElementName::DataElementTexture, 2, 6);
		vElement->addElementFromat(DataElementName::DataElementColor, 4, 8);
		real* data = (real*)vData->createData(8, vElement);
		memcpy(data, static_data, sizeof(static_data));

		IndeiceData* iData = WING_NEW IndeiceData();
		DataElement* iElement = WING_NEW DataElement(DataElementType::DataElementUInt,1);
		iElement->addElementFromat(DataElementName::DataElementIndice, 1, 0);
		uint32* indeice = (uint32*)iData->createData(sizeof(static_indice), iElement);
		memcpy(indeice, static_indice, sizeof(static_indice));
		
		vData->bindGPUBuffer();
		iData->bindGPUBuffer();

		setVertixData(vData);
		setIndeiceData(iData);

		GeometryPass* pass = WING_NEW GeometryPass();
		pass->init();
		setRenderPass(pass);

		scale(Vectorf(0.5, 0.5, 0.5));
	}

	Cube::~Cube()
	{

	}

}