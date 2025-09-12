#pragma once
#include "base/Console.h"
#include "base/embedded/dma/MemoryDma.h"
#include "base/string/define.h"
#include "base/string/ToHexString.h"
#include <cstddef>
#include <cstdint>
#include <exception>

namespace base
{
	namespace test
	{
		///
		/// @brief
		///
		/// @param dma_id
		/// @return
		///
		template <size_t Align>
		inline void TestMemoryDma(uint32_t dma_id)
		{
			base::memory_dma::MemoryDma memory_dma{dma_id};
			memory_dma.Initialize(Align);

			struct Data
			{
				alignas(Align) uint8_t src_buffer[16] =
					{1, 2, 3, 4, 5, 6, 7,
					 8, 9, 10, 11, 12, 13, 14, 15, 16};

				alignas(Align) uint8_t dst_buffer[16]{};
			};

			Data data;

			try
			{
				base::console().WriteLine(base::ToHexString(data.src_buffer));
				base::console().WriteLine(base::ToHexString(data.dst_buffer));
				for (size_t i = 0; i < 16; i++)
				{
					base::console().Write(base::ToHexString(data.dst_buffer[i]));
					base::console().Write(", ");
				}

				base::console().WriteLine();
				memory_dma.Copy(data.src_buffer, data.src_buffer + 8, data.dst_buffer);

				for (size_t i = 0; i < 16; i++)
				{
					base::console().Write(base::ToHexString(data.dst_buffer[i]));
					base::console().Write(", ");
				}

				base::console().WriteLine();
			}
			catch (std::exception const &e)
			{
				base::console().WriteError(CODE_POS_STR + e.what());
			}
			catch (...)
			{
				base::console().WriteError(CODE_POS_STR + "未知异常。");
			}
		}

		///
		/// @brief
		///
		/// @param dma_id
		/// @return
		///
		template <size_t Align>
		inline void TestMemoryDma1(uint32_t dma_id)
		{
			base::memory_dma::MemoryDma memory_dma{dma_id};
			memory_dma.Initialize(Align);

			struct Data
			{
				alignas(Align) uint32_t src_buffer[16] =
					{0xffff'fff1, 0xffff'fff2, 0xffff'fff3, 0xffff'fff4,
					 0xffff'fff5, 0xffff'fff6, 0xffff'fff7, 0xffff'fff8,
					 0xffff'fff9, 0xffff'ff10, 0xffff'ff11, 0xffff'ff12,
					 0xffff'ff13, 0xffff'ff14, 0xffff'ff15, 0xffff'ff16};

				alignas(Align) uint32_t dst_buffer[16]{};
			};

			Data data;

			try
			{
				base::console().WriteLine(base::ToHexString(data.src_buffer));
				base::console().WriteLine(base::ToHexString(data.dst_buffer));
				for (size_t i = 0; i < 16; i++)
				{
					base::console().Write(base::ToHexString(data.dst_buffer[i]));
					base::console().Write(", ");
				}

				base::console().WriteLine();
				memory_dma.Copy(data.src_buffer, data.src_buffer + 8, data.dst_buffer);

				for (size_t i = 0; i < 16; i++)
				{
					base::console().Write(base::ToHexString(data.dst_buffer[i]));
					base::console().Write(", ");
				}

				base::console().WriteLine();
			}
			catch (std::exception const &e)
			{
				base::console().WriteError(CODE_POS_STR + e.what());
			}
			catch (...)
			{
				base::console().WriteError(CODE_POS_STR + "未知异常。");
			}
		}

	} // namespace test
} // namespace base
