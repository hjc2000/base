#pragma once
#include "base/embedded/serial/Serial.h"
#include "base/IDisposable.h"
#include "base/math/Fraction.h"
#include "base/stream/BlockingCircleBufferMemoryStream.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "base/task/delay.h"
#include "base/task/ITask.h"
#include "base/task/task.h"
#include "base/unit/Seconds.h"
#include <chrono>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	namespace modbus
	{
		class ModbusSlave :
			public base::IDisposable
		{
		private:
			std::shared_ptr<base::serial::Serial> _serial{};
			bool _use_software_timeout = false;
			std::shared_ptr<base::BlockingCircleBufferMemoryStream> _received_stream{};
			std::shared_ptr<base::task::ITask> _read_thread_exit{};
			std::chrono::nanoseconds _timeout{};
			bool _disposed = false;

			void ReadThreadFunc()
			{
				uint8_t buffer[128];
				base::Span span{buffer, sizeof(buffer)};

				while (true)
				{
					if (_disposed)
					{
						return;
					}

					int32_t have_read = _serial->Read(span);
					_received_stream->Write(base::ReadOnlySpan{buffer, have_read});
				}
			}

		public:
			///
			/// @brief
			///
			/// @param serial 串口对象。
			/// @param use_software_timeout 是否启用软件超时进行断帧。
			///
			ModbusSlave(std::shared_ptr<base::serial::Serial> const &serial,
						bool use_software_timeout)
			{
				if (serial == nullptr)
				{
					throw std::invalid_argument{CODE_POS_STR + "不能传入空指针。"};
				}

				_serial = serial;
				_use_software_timeout = use_software_timeout;

				if (use_software_timeout)
				{
					_received_stream = std::shared_ptr<base::BlockingCircleBufferMemoryStream>{new base::BlockingCircleBufferMemoryStream{1024}};

					uint32_t baud_rate = _serial->BaudRate();
					uint32_t frames_baud_count = _serial->FramesBaudCount(3);
					base::Seconds timeout_seconds{base::Fraction{frames_baud_count, baud_rate}};
					_timeout = static_cast<std::chrono::nanoseconds>(timeout_seconds);

					_read_thread_exit = base::task::run(
						[this]()
						{
							ReadThreadFunc();
						});
				}
			}

			~ModbusSlave()
			{
				Dispose();
			}

			///
			/// @brief 处置对象，让对象准备好结束生命周期。类似于进入 “准备后事” 的状态。
			///
			/// @note 注意，对象并不是析构了，并不是完全无法访问，它仍然允许访问，仍然能执行一些
			/// 符合 “准备后事” 的工作。
			///
			virtual void Dispose() override
			{
				if (_disposed)
				{
					return;
				}

				_disposed = true;

				if (_use_software_timeout)
				{
					_received_stream->Close();
					_read_thread_exit->Wait();
				}
			}

			int32_t Read(base::Span const &span)
			{
				if (!_use_software_timeout)
				{
					// 使用硬件断帧，直接使用串口对象读取。
					int32_t have_read = _serial->Read(span);
					return have_read;
				}

				int32_t have_read = 0;

				while (true)
				{
					have_read += _received_stream->Read(span);
					base::task::Delay(_timeout);
					if (_received_stream->Length() == 0)
					{
						// 等待超时时间后没有新的数据到来，断帧。
						return have_read;
					}
				}
			}
		};

	} // namespace modbus
} // namespace base
