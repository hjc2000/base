#pragma once

namespace base
{
	namespace Enum
	{
		///
		/// @brief 有效状态。
		///
		///
		enum class ValidState
		{
			Invalid,
			Valid,
		};

		///
		/// @brief 错误状态。
		///
		///
		enum class FaultState
		{
			///
			/// @brief 无错误。
			///
			///
			HasNoFault,

			///
			/// @brief 有错误。
			///
			///
			HasFault,
		};
	} // namespace Enum
} // namespace base
