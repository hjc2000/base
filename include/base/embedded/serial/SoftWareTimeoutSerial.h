#pragma once
#include "base/embedded/serial/Serial.h"
#include "base/exception/NotSupportedException.h"
#include "base/stream/BlockingCircleBufferMemoryStream.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include "base/task/ITask.h"
#include "base/task/task.h"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>

namespace base
{
	namespace serial
	{
		///
		/// @brief 通过软件超时支持读取超时的串口。
		///
		///
		class SoftWareTimeoutSerial final :
			public base::Stream
		{
		private:
			std::shared_ptr<base::serial::Serial> _serial{};
			std::shared_ptr<base::BlockingCircleBufferMemoryStream> _receiving_stream{};
			std::shared_ptr<base::task::ITask> _receiving_thread_exit{};
			std::chrono::nanoseconds _receiving_timeout{};
			bool _closed = false;

			void Initialize(std::shared_ptr<base::serial::Serial> const &serial,
							int64_t receiving_buffer_size,
							int64_t timeout_frame_count);

			void ReceivingThreadFunc();

		public:
			///
			/// @brief
			///
			/// @param serial 串口对象。
			/// @param receiving_buffer_size 接收缓冲区大小。
			/// @param timeout_frame_count 超时时间是几个串行帧的时间。
			///
			SoftWareTimeoutSerial(std::shared_ptr<base::serial::Serial> const &serial,
								  int64_t receiving_buffer_size,
								  int64_t timeout_frame_count)
			{
				Initialize(serial, receiving_buffer_size, timeout_frame_count);

				_receiving_thread_exit = base::task::run(
					[this]()
					{
						ReceivingThreadFunc();
					});
			}

			///
			/// @brief
			///
			/// @param serial 串口对象。
			/// @param receiving_buffer_size 接收缓冲区大小。
			/// @param timeout_frame_count 超时时间是几个串行帧的时间。
			/// @param receiving_thread_stack_size 接收线程的堆栈大小。
			///
			SoftWareTimeoutSerial(std::shared_ptr<base::serial::Serial> const &serial,
								  int64_t receiving_buffer_size,
								  int64_t timeout_frame_count,
								  size_t receiving_thread_stack_size)
			{
				Initialize(serial, receiving_buffer_size, timeout_frame_count);

				_receiving_thread_exit = base::task::run(receiving_thread_stack_size,
														 [this]()
														 {
															 ReceivingThreadFunc();
														 });
			}

			~SoftWareTimeoutSerial()
			{
				Close();
			}

			/* #region 启动串口 */

			void Start(base::serial::Direction direction,
					   base::serial::BaudRate const &baud_rate,
					   base::serial::DataBits const &data_bits,
					   base::serial::Parity parity,
					   base::serial::StopBits stop_bits,
					   base::serial::HardwareFlowControl hardware_flow_control)
			{
				_serial->Start(direction, baud_rate, data_bits, parity, stop_bits, hardware_flow_control);
			}

			///
			/// @brief 启动串口。
			///
			///
			void Start()
			{
				_serial->Start();
			}

			///
			/// @brief 启动串口。
			///
			/// @param baud_rate
			///
			void Start(base::serial::BaudRate const &baud_rate)
			{
				_serial->Start(baud_rate);
			}

			/* #endregion */

			/* #region 流属性 */

			///
			/// @brief 本流能否读取。
			///
			/// @return true 能读取。
			/// @return false 不能读取。
			///
			virtual bool CanRead() const override
			{
				return true;
			}

			///
			/// @brief 本流能否写入。
			///
			/// @return true 能写入。
			/// @return false 不能写入。
			///
			virtual bool CanWrite() const override
			{
				return _serial->CanWrite();
			}

			///
			/// @brief 本流能否定位。
			///
			/// @return true 能定位。
			/// @return false 不能定位。
			///
			virtual bool CanSeek() const override
			{
				return false;
			}

			///
			/// @brief 流的长度
			///
			/// @return int64_t
			///
			virtual int64_t Length() const override
			{
				return _receiving_stream->Length();
			}

			///
			/// @brief 设置流的长度。
			///
			/// @param value
			///
			virtual void SetLength(int64_t value) override
			{
				throw base::NotSupportedException{};
			}

			///
			/// @brief 流当前的位置。
			///
			/// @return int64_t
			///
			virtual int64_t Position() const override
			{
				throw base::NotSupportedException{};
			}

			///
			/// @brief 设置流当前的位置。
			///
			/// @param value
			///
			virtual void SetPosition(int64_t value) override
			{
				throw base::NotSupportedException{};
			}

			/* #endregion */

			/* #region 读写冲关 */

			///
			/// @brief 将本流的数据读取到 span 中。
			///
			/// @param span
			/// @return int64_t
			///
			virtual int64_t Read(base::Span const &span) override;

			///
			/// @brief 将 span 中的数据写入本流。
			///
			/// @param span
			///
			virtual void Write(base::ReadOnlySpan const &span) override
			{
				_serial->Write(span);
			}

			///
			/// @brief 冲洗流。
			///
			/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
			/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
			///
			virtual void Flush() override
			{
				_serial->Flush();
			}

			///
			/// @brief 关闭流。
			///
			/// @note 关闭后流无法写入，写入会引发异常。
			///
			/// @note 关闭后流的读取不会引发异常，但是在读完内部残留的数据后，将不会再读到
			/// 任何数据。
			///
			virtual void Close() override
			{
				if (_closed)
				{
					return;
				}

				_closed = true;

				_serial->Close();
				_receiving_stream->Close();
				_receiving_thread_exit->Wait();
			}

			/* #endregion */
		};

	} // namespace serial
} // namespace base
