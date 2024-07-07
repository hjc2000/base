#pragma once
#include <memory>

namespace base
{
	template <typename FactoryType>
	class FactoryManager
	{
	private:
		std::shared_ptr<FactoryType> _costom_factory = nullptr;

	public:
		virtual ~FactoryManager() = default;

		/// @brief 设置了自定义工厂后就会返回自定义工厂，否则返回默认工厂。
		/// @return
		std::shared_ptr<FactoryType> Factory()
		{
			if (_costom_factory)
			{
				return _costom_factory;
			}

			return DefaultFactory();
		}

		void SetCustomFactory(std::shared_ptr<FactoryType> o)
		{
			_costom_factory = o;
		}

		virtual std::shared_ptr<FactoryType> DefaultFactory() = 0;
	};
} // namespace base
