#pragma once

namespace base
{
	template <typename T>
	class IConsumer
	{
	public:
		/// @brief 向消费者送入数据
		/// @param data
		virtual void SendData(T &data) = 0;

		/// @brief 冲洗消费者
		virtual void Flush() = 0;
	};
} // namespace base
