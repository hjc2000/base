#pragma once
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace base
{
	template <typename TRet>
	TRet Parse(std::string const &param)
	{
		throw std::runtime_error{"此重载未实现"};
	}

	/// @brief 特化版本：从 std::string 解析为 int
	/// @param param
	/// @return
	template <>
	int Parse<int>(std::string const &param)
	{
		return std::stoi(param);
	}

	/// @brief 特化版本：从 std::string 解析为 double
	/// @param param
	/// @return
	template <>
	double Parse<double>(std::string const &param)
	{
		return std::stod(param);
	}
}