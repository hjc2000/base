#pragma once
#include <cstdint>

namespace base
{
	class ColumnCount
	{
	private:
		int64_t _value{};

	public:
		constexpr ColumnCount() = default;

		explicit constexpr ColumnCount(int64_t value)
			: _value(value)
		{
		}

		constexpr int64_t Value() const
		{
			return _value;
		}

		constexpr void SetValue(int64_t value)
		{
			_value = value;
		}
	};

} // namespace base
