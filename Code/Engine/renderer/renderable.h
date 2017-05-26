#ifndef _WING_ENGINE_RENDERABLE_H_
#define _WING_ENGINE_RENDERABLE_H_

#include "scene\node.h"
#include "material.h"
#include "vertix_data.h"
#include "indeice_data.h"

namespace WingEngine
{


	class WING_ENGINE_API Renderable : public Node
	{

	public:

		Renderable();
		~Renderable();

		VertixData getVertixData() { return *mVertixData; }
		void setVertixData(VertixData* vertrixdata) { mVertixData = vertrixdata; }

		
	private:

		SmartPtr<VertixData> mVertixData;
		SmartPtr<IndeiceData> mIndeiceData;

	};


}

#endif