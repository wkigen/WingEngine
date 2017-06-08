#ifndef _WING_ENGINE_RESOURCE_SYSTEM_H_
#define _WING_ENGINE_RESOURCE_SYSTEM_H_


#include "base\smart_ptr.h"
#include "base\singleton.h"
#include "resource.h"
#include <map>
#include "log\log.h"
#include "io\file_system.h"
#include "common\engine_defines.h"
#include "resource_reader.h"
#include "resource_writer.h"
#include "allocator\allocator.h"

using namespace WingCore;

namespace WingEngine
{
	
	class WING_ENGINE_API ResourceSystem:public Singleton<ResourceSystem>
	{
		friend class Singleton<ResourceSystem>;

	public:
		virtual ~ResourceSystem();

		bool create();
		void destroy();

		template<class T>
		T* loadResource(std::string name);

		void addWriter(uint32 type, ResourceWriter* writer);
		void addReader(uint32 type, ResourceReader* reader);
		
	private:
		ResourceSystem();
		


	private:

		bool				mCreate;


		std::map<std::string, SmartPtr<Resource>>	mResource[ResourceTypeMax];
		std::map<uint32, ResourceWriter*>			mResourceWriters;
		std::map<uint32, ResourceReader*>			mResourceReaders;
	};
	



	template<class T>
	T* ResourceSystem::loadResource(std::string name)
	{
		uint32 type = T::getResourceType();
		std::map<uint32, ResourceReader*>::iterator itor = mResourceReaders.find(type);
		if (itor != mResourceReaders.end())
		{
			FileStream stream;
			if (FileSystem::getInstance()->openFile(name, stream,ACCESS::Read))
			{
				T* resource = WING_NEW T();
				itor->second->setStream(stream);
				itor->second->readResource<T>(resource);
				mResource[type] = resource;
				return resource;
			}
		}
		else
		{
			WING_LOG_WARN("is't exist reader of type[%d]", type);
		}
		return nullptr;
	}

}


#endif