#pragma once

namespace base
{
	/// @brief 句柄包装对象。
	/// @note 与在 ffmpeg-wrapper 中大量使用的 Wrapper 类不同，Wrapper 类是包装
	/// 位于堆上的对象的，Wrapper<T> 类中持有的是 T* 字段，而不是 T 字段。而 HandleWrapper
	/// HandleWrapper<T> 持有的是 T 字段而不是 T* 字段。即句柄包装类直接将句柄本身作为
	/// 自己的字段，而不是在堆上构造一个句柄对象然后将指向它的指针作为字段。
	///
	/// @tparam T
	template <typename T>
	class HandleWrapper
	{
	public:
		virtual ~HandleWrapper() = default;

		virtual T &Handle() = 0;

		T *operator->()
		{
			return &Handle();
		}

		operator T *()
		{
			return &Handle();
		}
	};
}
