#include "string_utils.h"

namespace WingCore
{
	inline uint64 StringUtils::covertInt(std::string str)
	{
		return convertNumeric<uint64>(str);
	}

	inline real StringUtils::covertReal(std::string str)
	{
		return convertNumeric<real>(str);
	}

	inline std::string StringUtils::covertString(uint64 value)
	{
		return covertString<uint64>(value);
	}

	inline std::string StringUtils::covertString(real value)
	{
		return covertString<real>(value);
	}

	template<class T>
	inline T StringUtils::convertNumeric(std::string str)
	{
		T value;
		std::stringstream ss(str);
		ss >> value;
		return value;
	}

	template<class T>
	inline std::string StringUtils::covertString(T value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}



}