#include "cube.h"
#include "pass\base_pass.h"

namespace WingEngine
{

	real static_data[] = 
	{
		-1.0,-1.0,1.0,   0.0,0.0,0.0,  0.0,0.0,
		1.0,-1.0,1.0,   0.0,0.0,0.0,  1.0,0.0,
		1.0,1.0,1.0,   0.0,0.0,0.0,  1.0,1.0,
		-1.0,1.0,1.0,   0.0,0.0,0.0,  0.0,1.0,

		-1.0,-1.0,-1.0,   0.0,0.0,0.0,  0.0,0.0,
		1.0,-1.0,-1.0,   0.0,0.0,0.0,  1.0,0.0,
		1.0,1.0,-1.0,   0.0,0.0,0.0,  1.0,1.0,
		-1.0,1.0,-1.0,   0.0,0.0,0.0,  0.0,1.0,
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
		IndeiceData* iData = WING_NEW IndeiceData();
		real* data = (real*)vData->createData(8);
		uint32* indeice = (uint32*)iData->createData(sizeof(static_indice));

		memcpy(data, static_data, sizeof(static_data));
		memcpy(indeice, static_indice, sizeof(static_indice));
		
		vData->bindGPUBuffer();
		iData->bindGPUBuffer();

		setVertixData(vData);
		setIndeiceData(iData);

		BasePass* pass = WING_NEW BasePass(this);
		pass->init();
		setRenderPass(pass);
	}

	Cube::~Cube()
	{

	}

}