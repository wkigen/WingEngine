#ifndef _WING_CORE_RESOURCE_SYSTEM_H_
#define _WING_CORE_RESOURCE_SYSTEM_H_

#include "base\singleton.h"
#include "resource.h"
#include "config\config.h"
#include "io\writer.h"
#include "io\reader.h"
#include <map>
#include "log\log.h"
#include "io\file_system.h"

namespace WingCore
{
	
	class ResourceSystem:public Singleton<ResourceSystem>
	{
		friend class Singleton<ResourceSystem>;

	public:
		virtual ~ResourceSystem();

		bool create();
		void destroy();

		template<class T>
		T* loadResource(std::string name);

		void addWriter(uint32 type, Writer* writer);
		void addReader(uint32 type, Reader* reader);
		
	private:
		ResourceSystem();
		


	private:
		std::map<std::string, Resource>			mResource[ResourceTypeMax];
		std::map<uint32, Writer*>	mResourceWriters;
		std::map<uint32, Reader*>	mResourceReaders;
	};
	
	template<class T>
	T* ResourceSystem::loadResource(std::string name)
	{
		ResourceType::Enum type = T::getResourceType();
		std::map<ResourceType::Enum, Reader*>::iterator itor = mResourceReaders.find(type);
		if (itor != mResourceWriters.end())
		{
			FileStream stream;
			if (FileSystem::getInstance()->openFile(name, stream,ACCESS::Read))
			{
				itor->second->setStream(stream);
				T* resource = WING_NEW T();
			}
		}
		else
		{
			WING_LOG_WARN("is't exist writer of type[%d]", type);
		}
		return nullptr;
	}

}


#endif