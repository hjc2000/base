#pragma once
#include <base/define.h>
#include <base/Guard.h>
#include <base/LockGuard.h>
#include <base/string/define.h>
#include <memory>

namespace base
{
	///
	/// @brief 单例获取器。
	///
	///
	template <typename T>
	class SingletonGetter :
		protected base::ILock
	{
	private:
		inline static_field std::unique_ptr<T> _p;

	protected:
		virtual std::unique_ptr<T> Create() = 0;
		virtual void Lock() = 0;
		virtual void Unlock() = 0;

	public:
		///
		/// @brief 获取单例的引用
		///
		/// @return T&
		///
		T &Instance()
		{
			if (_p != nullptr)
			{
				return *_p;
			}

			base::LockGuard l{*this};
			if (_p != nullptr)
			{
				return *_p;
			}

			_p = Create();
			if (_p == nullptr)
			{
				throw std::runtime_error{"禁止将 Create 函数实现为返回空指针。"};
			}

			return *_p;
		}

		///
		/// @brief 重载解引用运算符，用来获取单例的引用。
		///
		/// @return T&
		///
		T &operator*()
		{
			return Instance();
		}

		///
		/// @brief 重载指针式的成员访问运算符，用来访问单例对象的成员。
		///
		/// @return T*
		///
		T *operator->()
		{
			return &Instance();
		}
	};
} // namespace base
