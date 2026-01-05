#pragma once
#include <memory>

namespace base
{
	///
	/// @brief 借用指针工厂
	///
	class RentedPtrFactory final
	{
	private:
		RentedPtrFactory() = delete;

	public:
		///
		/// @brief 创建一个借用指针。
		///
		/// @note 借用指针实际上是一格共享指针，这个共享指针的删除器什么也不做，不会释放内存。
		///
		/// @note 这么做是为了让一些例如静态变量或手动管理生命周期的变量能够被 shared_ptr
		/// 套壳，从而兼容那些需要 shared_ptr 的 API。
		///
		/// @tparam T
		///
		/// @param o
		///
		/// @return
		///
		template <typename T>
		static std::shared_ptr<T> Create(T *o)
		{
			std::shared_ptr<T> ret{
				o,
				[](T *o)
				{
				},
			};

			return ret;
		}
	};

} // namespace base
