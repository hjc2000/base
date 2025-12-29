#pragma once
#include "base/stream/ReadOnlySpan.h"

namespace base::profinet
{
	class DcpTlvReader
	{
	private:
		bool _has_name_of_station_block = false;
		std::string _station_name;

	public:
		///
		/// @brief 构造函数。
		///
		/// @param span 去掉 DCP 头部后，剩下的含有许多 Block 的内存段。
		///
		DcpTlvReader(base::ReadOnlySpan const &span);

		///
		/// @brief 是否具有站点名称块。
		///
		/// @return 有则返回 true，没有则返回 false.
		///
		bool HasNameOfStationBlock() const;

		///
		/// @brief 站点名称。
		///
		/// @note 只有 HasNameOfStationBlock 属性为 true 时本属性才有效。
		/// HasNameOfStationBlock 为 false 时访问本属性会抛出异常。
		///
		/// @return
		///
		std::string NameOfStation() const;
	};

} // namespace base::profinet
