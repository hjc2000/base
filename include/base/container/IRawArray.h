#pragma once

namespace base
{
	/// @brief 只要底层的储存方式是 C 风格的裸数组的容器，都可以继承本接口。
	/// @tparam ItemType
	template <typename ItemType>
	class IRawArray
	{
	public:
		/// @brief 数组的大小
		/// @return
		virtual int Count() const = 0;

		/// @brief 获取底层的缓冲区
		/// @return
		virtual ItemType *Buffer() = 0;

		/// @brief 获取底层的缓冲区
		/// @return
		virtual ItemType const *Buffer() const = 0;
	};
} // namespace base
