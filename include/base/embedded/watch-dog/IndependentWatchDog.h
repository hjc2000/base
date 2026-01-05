#pragma once
#include "independent_watch_dog_handle.h"
#include <chrono>
#include <cstdint>
#include <memory>

namespace base
{
	namespace independent_watch_dog
	{
		///
		/// @brief 独立看门狗。
		///
		class IndependentWatchDog
		{
		private:
			std::shared_ptr<base::independent_watch_dog::independent_watch_dog_handle> _handle;

		public:
			IndependentWatchDog(uint32_t id)
			{
				_handle = base::independent_watch_dog::open(id);
			}

			///
			/// @brief 初始化独立看门狗。
			///
			/// @param timeout 看门狗超时时间。
			///
			void Initialize(std::chrono::milliseconds const &timeout)
			{
				base::independent_watch_dog::initialize(*_handle, timeout);
			}

			///
			/// @brief 喂狗。
			///
			void Feed()
			{
				base::independent_watch_dog::feed(*_handle);
			}

			///
			/// @brief 看门狗超时时间。
			///
			/// @return
			///
			std::chrono::milliseconds Timeout() const
			{
				return base::independent_watch_dog::timeout(*_handle);
			}
		};

	} // namespace independent_watch_dog
} // namespace base
