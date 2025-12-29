#pragma once
#include <memory>

namespace base
{
	///
	/// @brief 工厂管理者
	///
	/// @tparam FactoryType 工厂类
	///
	/// @note 工厂类 FactoryType 应该是接口，而不是可实例化的非抽象类，这样工厂管理者才有
	/// 存在的意义。
	///
	template <typename FactoryType>
	class FactoryManager
	{
	private:
		///
		/// @brief 用来储存自定义工厂类对象。
		///
		std::shared_ptr<FactoryType> _costom_factory = nullptr;

	public:
		///
		/// @brief 获取工厂实例。
		///
		/// @note 设置了自定义工厂后就会返回自定义工厂，否则返回默认工厂。
		///
		/// @return 返回工厂类对象的共享指针。
		/// 	@note 返回共享指针而不是引用是因为如果返回的是自定义工厂类的话，自定义工厂类
		/// 	是随时可能被替换的，如果返回的是引用，自定义工厂类被替换时智能指针会把旧的工厂
		/// 	类对象给析构了，并释放内存，这就会引发内存错误。
		///
		std::shared_ptr<FactoryType> Factory()
		{
			// 利用共享指针的赋值运算符是原子操作这一特性，将 _costom_factory
			// 捕获到 ret 中，这样就不用在判断过程中对 _costom_factory 加锁了。
			std::shared_ptr<FactoryType> ret = _costom_factory;
			if (ret)
			{
				return ret;
			}

			ret = DefaultFactory();
			if (ret == nullptr)
			{
				throw std::runtime_error{"不存在默认工厂，必须设置自定义工厂。"};
			}

			return ret;
		}

		///
		/// @brief 设置自定义工厂
		///
		/// @param o
		///
		void SetCustomFactory(std::shared_ptr<FactoryType> o)
		{
			_costom_factory = o;
		}

		///
		/// @brief 默认工厂
		///
		/// @note 默认的工厂。如果不存在默认，可以实现为返回空指针。
		///
		/// @return
		///
		virtual std::shared_ptr<FactoryType> DefaultFactory() = 0;
	};

} // namespace base
