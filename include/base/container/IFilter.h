#pragma once

namespace base
{
	template <typename T>
	class IFilter
	{
	public:
		virtual ~IFilter() = default;

		///
		/// @brief 检测元素是否满足过滤条件（能否通过过滤器）。
		///
		/// @param value 要被检查的元素。
		///
		/// @return 能通过过滤器则返回 true, 否则返回 false.
		///
		virtual bool Pass(T const &value) const = 0;
	};

} // namespace base
