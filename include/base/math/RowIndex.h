#pragma once
#include <cstdint>

namespace base
{
	class RowIndex
	{
	private:
		int64_t _value{};

	public:
		constexpr RowIndex() = default;

		explicit constexpr RowIndex(int64_t value)
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
