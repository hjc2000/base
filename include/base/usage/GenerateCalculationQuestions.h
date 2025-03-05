#pragma once
#if HAS_THREAD
	#include <cstdint>

namespace base
{
	namespace usage
	{
		/**
		 * @brief 生成计算题。
		 *
		 * @param min 计算题中各项的最小值。
		 * @param max 计算题中各项的最大值。
		 */
		void GenerateCalculationQuestions(int32_t min, int32_t max);

		/**
		 * @brief 生成计算题。
		 *
		 */
		void GenerateCalculationQuestions();
	} // namespace usage
} // namespace base
#endif
