#pragma once
#include "base/container/Range.h"
#include "base/embedded/serial/Serial.h"
#include "base/exception/NotSupportedException.h"
#include "base/math/Fraction.h"
#include "base/stream/BlockingCircleBufferMemoryStream.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/stream/Stream.h"
#include "base/string/define.h"
#include "base/task/delay.h"
#include "base/task/ITask.h"
#include "base/task/task.h"
#include "base/unit/Second.h"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <stdexcept>

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
							int64_t timeout_frame_count)
			{
				if (serial == nullptr)
				{
					throw std::invalid_argument{CODE_POS_STR + "不能传入空指针。"};
				}

				_serial = serial;
				_receiving_stream = std::shared_ptr<base::BlockingCircleBufferMemoryStream>{new base::BlockingCircleBufferMemoryStream{receiving_buffer_size}};

				{
					uint32_t baud_rate = _serial->BaudRate();
					uint32_t frames_baud_count = _serial->FramesBaudCount(timeout_frame_count);
					base::unit::Second timeout_seconds{base::Fraction{frames_baud_count, baud_rate}};
					_receiving_timeout = static_cast<std::chrono::nanoseconds>(timeout_seconds);
				}
			}

			void ReceivingThreadFunc()
			{
				uint8_t buffer[128];
				base::Span span{buffer, sizeof(buffer)};

				while (true)
				{
					if (_closed)
					{
						return;
					}

					int64_t have_read = _serial->Read(span);
					_receiving_stream->Write(base::ReadOnlySpan{buffer, have_read});
				}
			}

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
			/// @return
			///
			virtual bool CanRead() const override
			{
				return true;
			}

			///
			/// @brief 本流能否写入。
			///
			/// @return
			///
			virtual bool CanWrite() const override
			{
				return _serial->CanWrite();
			}

			///
			/// @brief 本流能否定位。
			///
			/// @return
			///
			virtual bool CanSeek() const override
			{
				return false;
			}

			///
			/// @brief 流的长度
			///
			/// @return
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
			/// @return
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
			///
			/// @return
			///
			virtual int64_t Read(base::Span const &span) override
			{
				int64_t have_read = 0;

				while (true)
				{
					if (have_read >= span.Size())
					{
						break;
					}

					have_read += _receiving_stream->Read(span[base::Range{have_read, span.Size()}]);
					base::task::Delay(_receiving_timeout);
					if (_receiving_stream->Length() == 0)
					{
						// 等待超时时间后没有新的数据到来，断帧。
						break;
					}
				}

				return have_read;
			}

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
