#pragma once
#include "base/profidrive/fault/FaultMessage.h"
#include <cstdint>

namespace base::profidrive
{
	///
	/// @brief 故障状况。
	///
	///
	class FaultSituation
	{
	private:
		static constexpr int32_t _max_fault_message_count = 8;
		int32_t _fault_message_count = 0;
		base::profidrive::FaultMessage _fault_message_buffer[_max_fault_message_count]{};

	public:
		constexpr FaultSituation() = default;

		///
		/// @brief 最大的错误消息个数。由缓冲区大小决定。
		///
		/// @return
		///
		static constexpr int32_t MaxFaultMessageCount()
		{
			return _max_fault_message_count;
		}

		///
		/// @brief 添加一个故障消息。
		///
		/// @param fault_message
		///
		constexpr void AddFaultMessage(base::profidrive::FaultMessage const &fault_message)
		{
			if (_fault_message_count > 7)
			{
				// 数量达到 7 个以上后，想要继续添加，始终都往索引为 7 的位置写入，
				// 覆盖旧的错误消息。
				//
				// 即故障消息数量达到 8 个后，再添加新的故障消息，始终覆盖最后添加的第 8 个
				// 故障消息。
				_fault_message_count = 7;
			}

			_fault_message_buffer[_fault_message_count] = fault_message;
			_fault_message_count++;
		}

		///
		/// @brief 当前已添加的故障消息的个数。
		///
		/// @return
		///
		constexpr int32_t FaultMessageCount() const
		{
			return _fault_message_count;
		}

		///
		/// @brief 索引缓冲区中的故障消息。
		///
		/// @param index
		/// @return
		///
		constexpr base::profidrive::FaultMessage const &operator[](int32_t index) const
		{
			return _fault_message_buffer[index];
		}
	};

} // namespace base::profidrive
