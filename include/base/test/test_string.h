#pragma once

/**
 * @brief 测试代码
 *
 */
#if HAS_THREAD

namespace base
{
	namespace test
	{
		/**
		 * @brief 测试 LastIndexOf.
		 *
		 */
		void Test_String_LastIndexOf();

		/**
		 * @brief 测试 Replace.
		 *
		 */
		void Test_String_Replace();

		/**
		 * @brief 测试 StartWith, EndWith.
		 *
		 */
		void Test_String_StartWith_EndWith();
	} // namespace test
} // namespace base

#endif
