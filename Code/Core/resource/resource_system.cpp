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
		return true;
	}

	void ResourceSystem::destroy()
	{

	}

	void ResourceSystem::addWriter(uint32 type, Writer* writer)
	{
		std::map<uint32, Writer*>::iterator itor = mResourceWriters.find(type);
		if (itor == mResourceWriters.end())
			WING_LOG_WARN("is exist writer of type[%d]",type);

		mResourceWriters[type] = writer;
	}

	void ResourceSystem::addReader(uint32 type, Reader* reader)
	{
		std::map<uint32, Reader*>::iterator itor = mResourceReaders.find(type);
		if (itor == mResourceReaders.end())
			WING_LOG_WARN("is exist reader of type[%d]", type);

		mResourceReaders[type] = reader;
	}

}