#include "resource_system.h"
#include "mesh\mesh_reader.h"
#include "image_reader.h"

namespace WingEngine
{
	ResourceSystem::ResourceSystem()
	{

	}

	ResourceSystem::~ResourceSystem()
	{

	}

	bool ResourceSystem::create()
	{
		if (mCreate)
		{
			WING_LOG_WARN("ResourceSystem has been create");
			return false;
		}
		mCreate = true;

		MeshReader* meshReader = WING_NEW MeshReader();
		ImageReader* imageReader = WING_NEW ImageReader();


		addReader(ResourceTypeMesh, meshReader);
		addReader(ResourceTypeImage, imageReader);

		return true;
	}

	void ResourceSystem::destroy()
	{

	}

	void ResourceSystem::addWriter(uint32 type, ResourceWriter* writer)
	{
		std::map<uint32, ResourceWriter*>::iterator itor = mResourceWriters.find(type);
		if (itor == mResourceWriters.end())
			WING_LOG_WARN("is exist writer of type[%d]",type);

		mResourceWriters[type] = writer;
	}

	void ResourceSystem::addReader(uint32 type, ResourceReader* reader)
	{
		std::map<uint32, ResourceReader*>::iterator itor = mResourceReaders.find(type);
		if (itor == mResourceReaders.end())
			WING_LOG_WARN("is exist reader of type[%d]", type);

		mResourceReaders[type] = reader;
	}

}