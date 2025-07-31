#include "SoftWareTimeoutSerial.h" // IWYU pragma: keep
#include "base/container/Range.h"
#include "base/math/Fraction.h"
#include "base/string/define.h"
#include "base/task/delay.h"
#include "base/unit/Second.h"
#include <stdexcept>

void base::serial::SoftWareTimeoutSerial::Initialize(std::shared_ptr<base::serial::Serial> const &serial,
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

void base::serial::SoftWareTimeoutSerial::ReceivingThreadFunc()
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

int64_t base::serial::SoftWareTimeoutSerial::Read(base::Span const &span)
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
