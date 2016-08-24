#ifndef _WING_CONGIF_STREAM_H_
#define _WING_CONGIF_STREAM_H_

#include <string>
#include "common\defines.h"
#include "config_group.h"
#include "resource\resource.h"

namespace WingCore
{
	class WING_CORE_API Config:public Resource
	{
		RESOURCE_TYPE(ResourceType::CONFIG)
	public:
		Config();
		~Config();

		bool addGroup(ConfigGroup group);
		bool removeGroup(std::string name);
		bool isExistGroup(std::string name);
		ConfigCroups getGroup() const;

		void setAttribute(std::string group, std::string att, std::string value);
		void setAttribute(std::string group, std::string att, real value);

		void getAttrbute(std::string group, std::string att, std::string& value);
		void getAttrbute(std::string group, std::string att, real& value);

		void removeAttribute(std::string group, std::string att);

	private:

		void setAttribute(std::string group, std::string att, std::string str, ConfigAttributeType::Enum type);

	private:

		std::string		mName;
		ConfigCroups	mGroups;
	};
}

#endif