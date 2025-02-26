#pragma once
#include <base/string/String.h>
#include <stdint.h>

namespace base
{
	int32_t ParseInt32(base::String const &str);
	int32_t ParseInt32(base::String const &str, int32_t base);

	int64_t ParseInt64(base::String const &str);
	int64_t ParseInt64(base::String const &str, int32_t base);

	double ParseDouble(base::String const &str);
	double ParseDouble(base::String const &str, int32_t base);
} // namespace base
