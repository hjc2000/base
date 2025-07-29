#pragma once

namespace base
{
	template <typename T>
	class IConsumer
	{
	public:
		virtual ~IConsumer() = default;

		///
		/// @brief 向消费者送入数据
		///
		/// @param data 要送给消费者的数据。
		/// 	@note 这里采用的是引用而不是 const 引用，是因为有些消费者是数据编辑器，
		/// 	它们被串联在数据流管道中，对数据进行加工。
		///
		virtual void SendData(T &data) = 0;

		///
		/// @brief 冲洗消费者
		///
		/// @note 通知消费者没有更多数据了，该清理缓冲区或其他地方的残留数据了。
		///
		virtual void Flush() = 0;
	};

} // namespace base
