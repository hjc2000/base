#pragma once
#include<memory>

namespace base
{
	template <class T>
	class Wrapper
	{
	private:
		Wrapper(Wrapper<T> const &o) = delete;
		void operator=(Wrapper<T> const &o) = delete;
		operator bool() = delete;

	public:
		Wrapper() = default;
		virtual ~Wrapper() = default;

		/// <summary>
		///		被包装对象一般应该是通过指针指向的位于堆中的对象，因为这样允许运行时更换被包装对象。
		///		本函数返回的是指针的引用，允许修改指针的指向。派生类如果不允许指针被修改记得将本函数
		///		实现为抛出异常 jc::NotSupportedException()。
		/// </summary>
		/// <returns></returns>
		virtual T *&WrappedObj() = 0;
		virtual T *WrappedObj() const = 0;

		/// <summary>
		///		如果被包装对象是空指针，则返回 true。
		/// </summary>
		/// <returns></returns>
		bool IsNull() const;

		/// <summary>
		///		访问本类中储存的被包装类型对象的指针
		/// </summary>
		/// <returns></returns>
		T *operator->() const;

		/// <summary>
		///		将本类对象强制转换为被包装类型的指针
		/// </summary>
		operator T *() const;

		/// <summary>
		///		将本类对象强制转换为被包装类型的指针的指针。
		///		本函数返回的是指针的指针，也就是可以用来将被包装对象替换成另一个对象。
		/// </summary>
		operator T **();

		bool operator==(Wrapper<T> const &o) const;
	};

	/* 实现 */

	template<class T>
	inline bool Wrapper<T>::IsNull() const
	{
		return WrappedObj() == nullptr;
	}

	template<class T>
	inline T *Wrapper<T>::operator->() const
	{
		return WrappedObj();
	}

	template<class T>
	inline Wrapper<T>::operator T *() const
	{
		return WrappedObj();
	}

	template<class T>
	inline Wrapper<T>::operator T **()
	{
		return &WrappedObj();
	}

	template<class T>
	inline bool Wrapper<T>::operator==(Wrapper<T> const &o) const
	{
		return WrappedObj() == o.WrappedObj();
	}
}
