#pragma once
#include <cstdint>

namespace base
{
	///
	/// @brief UTC 小时偏移。
	///
	class UtcHourOffset
	{
	private:
		int64_t _value{};

	public:
		///
		/// @brief UTC + 0.
		///
		///
		UtcHourOffset() = default;

		///
		/// @brief UTC + value.
		///
		/// @param value
		///
		explicit UtcHourOffset(int64_t value)
			: _value(value)
		{
		}

		///
		/// @brief 偏移的小时。
		///
		/// @return int64_t
		///
		int64_t Value() const
		{
			return _value;
		}
	};
} // namespace base
