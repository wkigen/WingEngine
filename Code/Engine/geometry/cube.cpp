#include "cube.h"
#include "pass\base_pass.h"

namespace WingEngine
{

	real static_data[8*3*3*2] = 
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

	uint32 static_indice[36]=
	{
		1,2,4,
		2,3,4,

		2,6,3,
		6,7,3,

		3,7,4,
		7,8,4,

		5,1,8,
		1,4,8,

		6,2,5,
		2,1,5,

		5,6,8,
		6,7,8,
	};

	Cube::Cube()
	{
		mRenderType = RenderTypeGeometry;

		VertixData* vData = WING_NEW VertixData();
		IndeiceData* iData = WING_NEW IndeiceData();
		real* data = (real*)vData->createData(8);
		uint32* indeice = (uint32*)iData->createData(36);

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