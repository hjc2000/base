#pragma once

namespace base
{
	namespace ethernet
	{
		///
		/// @brief 以太网控制器连接着 PHY 的接口类型。
		///
		///
		enum class InterfaceType
		{
			///
			/// @brief 独立介质接口。
			///
			MII,

			///
			/// @brief 精简独立介质接口。
			///
			RMII,
		};

		///
		/// @brief 双工模式
		///
		///
		enum class DuplexMode
		{
			///
			/// @brief 全双工
			///
			///
			FullDuplex,

			///
			/// @brief 半双工
			///
			///
			HalfDuplex,
		};

	} // namespace ethernet
} // namespace base
