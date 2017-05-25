#ifndef _WING_ENGINE_RENDERABLE_H_
#define _WING_ENGINE_RENDERABLE_H_

#include "scene\node.h"

namespace WingEngine
{


	class WING_ENGINE_API Renderable : public Node
	{

	public:
		Renderable();
		~Renderable();

		virtual real* createData(uint64 size);
		virtual uint32* createIndeice(uint64 size);

	private:

		//data struct
		//POSITION       NORMAL         TEXTURE_COORDINATE
		//3(real)        3(real)        2(real)
		real* mData;
		//indice struce
		//1(uint32)
		uint32* mIndeice;

	};


}

#endif