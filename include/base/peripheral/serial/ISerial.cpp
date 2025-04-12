#include "ISerial.h"

uint32_t base::serial::ISerial::FramesBaudCount(uint32_t frame_count) const
{
	uint32_t baud_count = 0;

	// 1 位起始位
	baud_count += 1 * frame_count;

	// DataBits().Value() 位数据位
	baud_count += DataBits() * frame_count;

	if (Parity() != base::serial::Parity::None)
	{
		// 1 位校验位
		baud_count += 1 * frame_count;
	}

	// 停止位
	switch (StopBits())
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

/* #region Open */

void base::serial::ISerial::Open()
{
	Open(base::serial::Direction::RX_TX,
		 base::serial::BaudRate{115200},
		 base::serial::DataBits{8},
		 base::serial::Parity::None,
		 base::serial::StopBits::One,
		 base::serial::HardwareFlowControl::None);
}

void base::serial::ISerial::Open(base::serial::BaudRate const &baud_rate)
{
	Open(base::serial::Direction::RX_TX,
		 baud_rate,
		 base::serial::DataBits{8},
		 base::serial::Parity::None,
		 base::serial::StopBits::One,
		 base::serial::HardwareFlowControl::None);
}

/* #endregion */
