#include "serial_handle.h"

uint32_t base::serial::frames_baud_count(base::serial::sp_serial_handle const &h, uint32_t frame_count)
{
	uint32_t baud_count = 0;

	// 1 位起始位
	baud_count += 1 * frame_count;

	// data_bits 位数据位
	baud_count += base::serial::data_bits(h) * frame_count;

	if (base::serial::parity(h) != base::serial::Parity::None)
	{
		// 1 位校验位
		baud_count += 1 * frame_count;
	}

	// 停止位
	switch (base::serial::stop_bits(h))
	{
	case base::serial::StopBits::ZeroPointFive:
		{
			// 每 2 个帧占用 1 个位。
			baud_count += frame_count / 2;

			// 还剩余半个位，当成 1 位。
			if (frame_count % 2 > 0)
			{
				baud_count += 1;
			}

			break;
		}
	default:
	case base::serial::StopBits::One:
		{
			baud_count += 1 * frame_count;
			break;
		}
	case base::serial::StopBits::OnePointFive:
		{
			// 每 2 个帧占用 3 个位。
			baud_count += (frame_count / 2) * 3;

			// 还剩余 1.5 个位，当成 2 位。
			if (frame_count % 2 > 0)
			{
				baud_count += 2;
			}

			break;
		}
	case base::serial::StopBits::Two:
		{
			baud_count += 2 * frame_count;
			break;
		}
	}

	return baud_count;
}
