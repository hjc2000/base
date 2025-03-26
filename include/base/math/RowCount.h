#pragma once

#include <cstdint>

namespace base
{
	class RowCount
	{
	private:
		int64_t _value{};

	public:
		RowCount() = default;

		explicit RowCount(int64_t value);

		int64_t Value() const
		{
			return _value;
		}

		void SetValue(int64_t value)
		{
			_value = value;
		}
	};
} // namespace base
