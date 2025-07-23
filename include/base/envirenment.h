#pragma once
#include "base/container/Dictionary.h"
#include "string/KeyValueString.h"
#include <string>
#include <vector>

#if HAS_THREAD

namespace base
{
	///
	/// @brief 获取环境变量。
	///
	/// @param name 环境变量名。
	/// @return
	///
	std::string GetEnvirenmentVariable(std::string const &name);

	///
	/// @brief 获取环境变量列表。
	///
	/// @return
	///
	std::vector<base::KeyValueString> GetEnvirenmentVariableVector();

	///
	/// @brief 获取环境变量字典。
	///
	/// @return
	///
	base::Dictionary<base::String, base::String> GetEnvirenmentVariableDictionary();

} // namespace base

#endif // HAS_THREAD
