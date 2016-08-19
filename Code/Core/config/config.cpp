#include "config.h"
#include "log\log.h"
#include "utils\string_utils.h"
namespace WingCore
{

	Config::Config()
	{

	}

	Config::~Config()
	{
	}

	bool Config::addGroup(ConfigGroup group)
	{
		ConfigCroups::iterator itor = mGroups.find(group.mName);
		if (itor != mGroups.end())
		{
			mGroups[group.mName]=group;
			return true;
		}
		WING_LOG_ERROR("the %s is not exist", group.mName.c_str());
		return false;
	}

	bool Config::removeGroup(std::string name)
	{
		ConfigCroups::iterator itor = mGroups.find(mName);
		if (itor != mGroups.end())
		{
			mGroups.erase(itor);
			return true;
		}
		WING_LOG_ERROR("the %s is not exist", name.c_str());
		return false;
	}

	bool Config::isExistGroup(std::string name)
	{
		ConfigCroups::iterator itor = mGroups.find(mName);
		if (itor != mGroups.end())
			return true;
		return false;
	}

	void Config::setAttribute(std::string group, std::string att, std::string value)
	{
		setAttribute(group, att, value, ConfigAttributeType::STRING);
	}

	void Config::setAttribute(std::string group, std::string att, real value)
	{
		setAttribute(group, att, StringUtils::covertString(value), ConfigAttributeType::NUMERIC);
	}

	void Config::setAttribute(std::string group, std::string att,std::string str, ConfigAttributeType::Enum type)
	{
		ConfigCroups::iterator itor = mGroups.find(group);
		if (itor != mGroups.end())
		{
			ConfigAttributes::iterator attriteItor = itor->second.mAttrubute.begin();
			while (attriteItor != itor->second.mAttrubute.end())
			{
				if (attriteItor->mName == att)
				{
					attriteItor->mObject = str;
					return;
				}
				attriteItor++;
			}
			ConfigAttribute attribute;
			attribute.mName = att;
			attribute.mObject = str;
			attribute.mType = type;
			itor->second.mAttrubute.push_back(attribute);
		}
		else
		{
			ConfigGroup newGroup;
			ConfigAttribute attribute;
			attribute.mName = att;
			attribute.mObject = str;
			attribute.mType = type;
			newGroup.mName = group;
			newGroup.mAttrubute.push_back(attribute);
			mGroups[group] = newGroup;
		}
	}

	void Config::getAttrbute(std::string group, std::string att, std::string& value)
	{
		ConfigCroups::iterator itor = mGroups.find(group);
		if (itor != mGroups.end())
		{
			ConfigAttributes::iterator attriteItor = itor->second.mAttrubute.begin();
			while (attriteItor != itor->second.mAttrubute.end())
			{
				if (attriteItor->mName == att)
				{
					value = attriteItor->mObject;
					return;
				}
				attriteItor++;
			}
		}
	}

	void Config::getAttrbute(std::string group, std::string att, real& value)
	{
		std::string val;
		getAttrbute(group, att, val);
		value = StringUtils::covertReal(val);
	}

	void Config::removeAttribute(std::string group, std::string att)
	{
		ConfigCroups::iterator itor = mGroups.find(group);
		if (itor != mGroups.end())
		{
			ConfigAttributes::iterator attriteItor = itor->second.mAttrubute.begin();
			while (attriteItor != itor->second.mAttrubute.end())
			{
				if (attriteItor->mName == att)
				{
					itor->second.mAttrubute.erase(attriteItor);
					return;
				}
				attriteItor++;
			}
		}
	}

	ConfigCroups Config::getGroup() const
	{
		return mGroups;
	}
}