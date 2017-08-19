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
		~ResourceSystem();

		bool create();
		void destroy();

		template<class T>
		SmartPtr<T> loadResource(std::string name);

		template<class T>
		SmartPtr<T> getResource(std::string name);

		void addWriter(uint32 type, SmartPtr<ResourceWriter> writer);
		void addReader(uint32 type, SmartPtr<ResourceReader> reader);
		
	private:
		ResourceSystem();
		

	private:

		bool				mCreate;

		std::map<std::string, SmartPtr<Resource>>			mResource[ResourceTypeMax];
		std::map<uint32, SmartPtr<ResourceWriter>>			mResourceWriters;
		std::map<uint32, SmartPtr<ResourceReader>>			mResourceReaders;
	};
	



	template<class T>
	SmartPtr<T> ResourceSystem::loadResource(std::string name)
	{
		uint32 type = T::StaticResourceType;
		std::map<uint32, SmartPtr<ResourceReader>>::iterator itor = mResourceReaders.find(type);
		if (itor != mResourceReaders.end())
		{
			FileStream stream;
			if (FileSystem::getInstance()->openFile(name, stream,ACCESS::Read))
			{
				SmartPtr<T> resource = WING_NEW T();
				itor->second->setStream(&stream);
				itor->second->readResource(resource);
				mResource[type][name] = resource;
				return resource;
			}
		}
		else
		{
			WING_LOG_WARN("isn't exist reader of type[%d]", type);
		}
		return nullptr;
	}

	template<class T>
	SmartPtr<T> ResourceSystem::getResource(std::string name)
	{
		uint32 type = T::StaticResourceType;
		std::map<std::string, SmartPtr<Resource>>::iterator itor = mResource[type].find(name);
		if (itor != mResource[type].end()) {
			return itor->second;
		}
		return nullptr;

	}



}


#endif