#pragma once
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace base
{
	struct ParseOptions
	{
		/// @brief 进制。
		int32_t _base = 10;
	};

	int32_t ParseInt32(std::string const &str, base::ParseOptions const &options = base::ParseOptions{});
	int64_t ParseInt64(std::string const &str, base::ParseOptions const &options = base::ParseOptions{});
	double ParseDouble(std::string const &str, base::ParseOptions const &options = base::ParseOptions{});
} // namespace base
