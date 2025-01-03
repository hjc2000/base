#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/string/define.h>
#include <DcpTlvEnumerable.h>
#include <stdexcept>

namespace base
{
	namespace profinet
	{
		class DcpTlvReader
		{
		private:
			base::profinet::DcpTlvEnumerable _tlv_collection;
			base::ReadOnlySpan _name_of_station_block;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			DcpTlvReader(base::ReadOnlySpan const &span);

#pragma region Blocks
			/// @brief 是否具有站点名称块。
			/// @return 有则返回 true，没有则返回 false.
			bool HasNameOfStationBlock() const;

			/// @brief 站点名称。
			/// @note 只有 HasNameOfStationBlock 属性为 true 时本属性才有效。
			/// HasNameOfStationBlock 为 false 时访问本属性会抛出异常。
			/// @return
			std::string NameOfStation() const;
#pragma endregion
		};
	} // namespace profinet
} // namespace base
