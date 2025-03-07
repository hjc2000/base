#pragma once

namespace base
{
	namespace profidrive
	{
		enum class DataTypeEnum
		{
			Bool = 1,
			Int8 = 2,
			Int16 = 3,
			Int32 = 4,
			Int64 = 55,
			UInt8 = 5,
			UInt16 = 6,
			UInt32 = 7,
			UInt64 = 56,
			Float32 = 8,
			Float64 = 15,
			VisibleString = 9,
			OctetString = 10,
			UnicodeString = 39,

			/**
			 * @brief 带日期指示的 TimeOfDay.
			 *
			 */
			TimeOfDay_WithDateIndication = 12,

			/**
			 * @brief 已经启用。新设备不应该使用。为了兼容旧设备，控制器应该支持，设备可以不支持。
			 *
			 */
			TimeDifference_Unused = 13,

			Date = 50,

			/**
			 * @brief 不带日期指示的 TimeOfDay.
			 *
			 */
			TimeOfDay_WithoutDateIndication = 52,

			/**
			 * @brief 带日期指示的 TimeDifference.
			 *
			 */
			TimeDifference_WithDateIndication = 53,

			/**
			 * @brief 不带日期指示的 TimeDifference.
			 *
			 */
			TimeDifference_WithoutDateIndication = 54,

			N2 = 113,
			N4 = 114,
			V2 = 115,
			L2 = 116,
			R2 = 117,
			T2 = 118,
			T4 = 119,
			D2 = 120,
			E2 = 121,
			C4 = 122,
			X2 = 123,
			X4 = 124,
		};
	} // namespace profidrive
} // namespace base
