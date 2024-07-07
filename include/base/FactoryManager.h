#pragma once
#include <memory>

namespace base
{
	template <typename T>
	class FactoryManager
	{
	private:
		static std::shared_ptr<T> &CustomFactory()
		{
			static std::shared_ptr<T> o = nullptr;
			return o;
		}

	public:
		static std::shared_ptr<T> Factory()
		{
			if (CustomFactory())
			{
				return CustomFactory();
			}

			return DefaultFactory();
		}

		static void SetCustomFactory(std::shared_ptr<T> o)
		{
			CustomFactory() = o;
		}

		/// @brief 用户在实例化模板后需要在源文件中提供此静态方法的实现。
		/// @return
		static std::shared_ptr<T> DefaultFactory()
		{
		}
	};
} // namespace base
