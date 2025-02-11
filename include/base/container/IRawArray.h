#pragma once
#include <base/container/ArraySpan.h>

namespace base
{
	/// @brief 只要底层的储存方式是 C 风格的裸数组的容器，都可以继承本接口。
	/// @tparam ItemType
	template <typename ItemType>
	class IRawArray
	{
	public:
#pragma region 接口
		/// @brief 数组的大小
		/// @return
		virtual int32_t Count() const = 0;

		/// @brief 获取底层的缓冲区
		/// @return
		virtual ItemType *Buffer() = 0;

		/// @brief 获取底层的缓冲区
		/// @return
		virtual ItemType const *Buffer() const = 0;
#pragma endregion

		/// @brief 翻转数组
		void Reverse()
		{
			std::reverse(Buffer(), Buffer() + Count());
		}

		base::ArraySpan<ItemType> AsSpan()
		{
			return base::ArraySpan<ItemType>{Buffer(), Count()};
		}

		base::ReadOnlyArraySpan<ItemType> AsReadOnlyArraySpan() const
		{
			return base::ReadOnlyArraySpan<ItemType>{Buffer(), Count()};
		}
	};
} // namespace base
