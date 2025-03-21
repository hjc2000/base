#pragma once
#include <cstdint>

namespace base
{
	class UtcHourOffset
	{
	private:
		int64_t _value{};

	public:
		UtcHourOffset() = default;

		explicit UtcHourOffset(int64_t value)
			: _value(value)
		{
		}

		int64_t Value() const
		{
			return _value;
		}
	};
} // namespace base
