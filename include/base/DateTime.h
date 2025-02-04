#pragma once
#if HAS_THREAD

#include <base/define.h>
#include <chrono>
#include <cstdint>
#include <ctime>

namespace base
{
	class DateTime final
	{
	public:
		/// @brief 用毫秒来获取当前的 UTC 时间。
		/// @note 试了下，精度似乎只到 10ms，因为输出的时候最后一位永远是 0。
		/// @return 用毫秒表示的 UTC 时间
		static_function int64_t GetRealTimeInMilliseconds();

		/// @brief 获取单调递增的时钟的时间。
		/// @note 这个时间可能是基于系统持续运行时间，所以不会因为调整日期时间而受影响，永远会单调递增。
		/// @return
		static_function int64_t GetSteadyTimeInMilliseconds();
	};
} // namespace base

#endif // HAS_THREAD
