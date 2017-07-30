#include "plane.h"
#include "pass\geometry_color_pass.h"
#include "renderer\renderer_system.h"
namespace WingEngine
{

	real static_plane_data[] = 
	{
		-1.0,0.0,1.0,   0.0,1.0,0.0,  0.0,0.0,  1.0,1.0,1.0,1.0,
		1.0,0.0,1.0,   0.0,1.0,0.0,  1.0,0.0,  1.0,1.0,1.0,1.0,
		1.0,0.0,-1.0,   0.0,1.0,0.0,  1.0,1.0,  1.0,1.0,1.0,1.0,
		-1.0,0.0,-1.0,   0.0,1.0,0.0,  0.0,1.0,  1.0,1.0,1.0,1.0,

	};

	uint32 static_plane_indice[]=
	{
		0,1,3,
		1,2,3,

	};

	Plane::Plane()
	{
		mRenderType = RenderTypeGeometry;

		SmartPtr<VertixData> vData = WING_NEW VertixData();
		SmartPtr<DataElement> vElement = WING_NEW DataElement(DataElementType::DataElementReal,12);
		vElement->addElementFromat(DataElementName::DataElementPosition, 3, 0);
		vElement->addElementFromat(DataElementName::DataElementNormal, 3, 3);
		vElement->addElementFromat(DataElementName::DataElementTexture, 2, 6);
		vElement->addElementFromat(DataElementName::DataElementColor, 4, 8);
		real* data = (real*)vData->createData(4, vElement);
		memcpy(data, static_plane_data, sizeof(static_plane_data));

		SmartPtr<IndeiceData> iData = WING_NEW IndeiceData();
		SmartPtr<DataElement> iElement = WING_NEW DataElement(DataElementType::DataElementUInt,1);
		iElement->addElementFromat(DataElementName::DataElementIndice, 1, 0);
		uint32* indeice = (uint32*)iData->createData(sizeof(static_plane_indice), iElement);
		memcpy(indeice, static_plane_indice, sizeof(static_plane_indice));
		
		vData->bindGPUBuffer();
		iData->bindGPUBuffer();

		setVertixData(vData);
		setIndeiceData(iData);

		scale(Vectorf(5, 5, 5));
	}

	Plane::~Plane()
	{

	}

}