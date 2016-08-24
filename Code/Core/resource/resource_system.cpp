#include "resource_system.h"


namespace WingCore
{
	ResourceSystem::ResourceSystem()
	{

	}

	ResourceSystem::~ResourceSystem()
	{

	}

	bool ResourceSystem::create()
	{

	}

	void ResourceSystem::destroy()
	{

	}

	void ResourceSystem::addWriter(ResourceType::Enum type, Writer* writer)
	{
		std::map<ResourceType::Enum, Writer*>::iterator itor = mResourceWriters.find(type);
		if (itor == mResourceWriters.end())
			WING_LOG_WARN("is exist writer of type[%d]",type);

		mResourceWriters[type] = writer;
	}

	void ResourceSystem::addReader(ResourceType::Enum type, Reader* reader)
	{
		std::map<ResourceType::Enum, Reader*>::iterator itor = mResourceReaders.find(type);
		if (itor == mResourceReaders.end())
			WING_LOG_WARN("is exist reader of type[%d]", type);

		mResourceReaders[type] = reader;
	}

}