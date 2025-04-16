#pragma once
#include "base/bit/bit.h"
#include "base/peripheral/sdram/SdramController.h"
#include <cstdint>

namespace base
{
	namespace sdram
	{
		namespace chip
		{
			namespace w9825g6kh_6
			{
				///
				/// @brief 读突发模式。
				///
				///
				enum class ReadingBurstMode
				{
					///
					/// @brief 连续地突发。
					///
					///
					Sequential,

					///
					/// @brief 交错地突发。
					///
					///
					Interleaved,
				};

				///
				/// @brief 写突发模式。
				///
				///
				enum class WritingBurstMode
				{
					///
					/// @brief 编程的突发模式。
					///
					///
					Programmed,

					///
					/// @brief 单点突发模式。即一次写入一个列，实际上就是不突发。
					///
					///
					Single,
				};

				class ModeRegister
				{
				private:
					uint32_t _value = 0;

				public:
					constexpr uint32_t Value() const
					{
						return _value;
					}

					constexpr uint32_t ReadingBurstLength() const
					{
						uint32_t value = base::bit::ReadBits(_value, 0, 3);
						value *= 2;
						if (value == 0)
						{
							value = 1;
						}

						return value;
					}

					constexpr void SetReadingBurstLength(uint32_t value)
					{
						base::bit::WriteBits(_value, 0, 3, value / 2);
					}

					constexpr base::sdram::chip::w9825g6kh_6::ReadingBurstMode ReadingBurstMode() const
					{
						if (base::bit::ReadBit(_value, 3))
						{
							return base::sdram::chip::w9825g6kh_6::ReadingBurstMode::Interleaved;
						}

						return ReadingBurstMode::Sequential;
					}

					constexpr void SetReadingBurstMode(base::sdram::chip::w9825g6kh_6::ReadingBurstMode value)
					{
						if (value == base::sdram::chip::w9825g6kh_6::ReadingBurstMode::Interleaved)
						{
							base::bit::WriteBit(_value, 3, true);
						}
						else
						{
							base::bit::WriteBit(_value, 3, false);
						}
					}

					constexpr base::sdram::chip::w9825g6kh_6::WritingBurstMode WritingBurstMode() const
					{
						if (base::bit::ReadBit(_value, 9))
						{
							return base::sdram::chip::w9825g6kh_6::WritingBurstMode::Single;
						}

						return base::sdram::chip::w9825g6kh_6::WritingBurstMode::Programmed;
					}
				};

				class W9825G6KH_6
				{
				private:
					base::sdram::SdramController _controller;

				public:
					///
					/// @brief 构造函数。
					/// @param controller 需要一个控制器来控制 SDRAM 芯片。
					///
					W9825G6KH_6(base::sdram::SdramController const &controller);

					///
					/// @brief 打开 SDRAM.
					///
					/// @note 分为 2 步：
					/// 	@li 打开 SDRAM 控制器。
					/// 	@li 初始化 SDRAM 芯片。
					///
					void Open();

					///
					/// @brief 此 SDRAM 的内存段。
					/// @return
					///
					base::Span Span() const;
				};
			} // namespace w9825g6kh_6
		} // namespace chip
	} // namespace sdram
} // namespace base
