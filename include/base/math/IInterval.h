#pragma once

namespace base
{
	template <typename T>
	class IInterval
	{
	public:
		///
		/// @brief 检查一个值是否在区间内。
		///
		/// @param value
		/// @return
		///
		virtual bool IsInRange(T const &value) const = 0;

		///
		/// @brief 检查一个值是否在区间外。
		///
		/// @param value
		/// @return
		///
		bool IsOutOfRange(T const &value) const
		{
			return !IsInRange(value);
		}
	};

} // namespace base
