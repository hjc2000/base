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

		///
		/// @brief 警告状态。
		///
		///
		enum class WarningState
		{
			///
			/// @brief 无警告。
			///
			///
			HasNoWarning,

			///
			/// @brief 有警告。
			///
			///
			HasWarning,
		};
	} // namespace Enum
} // namespace base
