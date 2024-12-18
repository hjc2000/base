#pragma once
#include <memory>

namespace base
{
	/// @brief 包装器。
	/// @note 包装器默认情况下是独占被包装对象，并且负责在析构函数中清理被包装对象的资源，
	/// 为了避免重复清理资源，默认情况下删除包装器的拷贝构造函数和赋值运算符。如果派生类
	/// 允许这种行为，可以自己定义它们。
	/// @tparam T
	template <class T>
	class Wrapper
	{
	private:
		Wrapper(Wrapper<T> const &o) = delete;
		void operator=(Wrapper<T> const &o) = delete;
		operator bool() = delete;

	public:
		/// @brief 允许无参构造。
		/// @note 因为拷贝构造函数被删除，如果这里不定义无参构造，将会造成
		/// 派生类无法构造。
		Wrapper() = default;

		/// @brief 获取被包装对象的指针。
		/// @return
		virtual T *WrappedObj() const = 0;

		/// @brief 如果被包装对象是空指针，则返回 true。
		/// @return
		bool IsNull() const
		{
			return WrappedObj() == nullptr;
		}

		/// @brief 访问本类中储存的被包装类型对象的指针。
		/// @return
		T *operator->() const
		{
			return WrappedObj();
		}

		/// @brief 将本类对象强制转换为被包装类型的指针。
		operator T *() const
		{
			return WrappedObj();
		}

		/// @brief 重载相等比较运算符。只有被包装对象的指针相同时才认为包装器相等。
		/// @param o
		/// @return
		bool operator==(Wrapper<T> const &o) const
		{
			return WrappedObj() == o.WrappedObj();
		}
	};
} // namespace base
