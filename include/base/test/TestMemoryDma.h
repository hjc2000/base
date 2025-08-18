#pragma once
#include "base/Console.h"
#include "base/embedded/dma/MemoryDma.h"
#include "base/string/ToHexString.h"
#include <cstddef>
#include <cstdint>

namespace base
{
	namespace test
	{
		template <size_t Align>
		inline void TestMemoryDma(uint32_t dma_id)
		{
			base::memory_dma::MemoryDma memory_dma{dma_id};
			memory_dma.Initialize(Align);

			///
			/// @brief 不知道为什么，直接在栈上放置数组变量，并使用 alignas, 对齐并没有正确
			/// 生效，这导致一旦使用 DMA 拷贝直接陷入 HardFault, 所以这里使用结构体来进行数组
			/// 的对齐。
			///
			struct Data
			{
				alignas(Align) uint8_t src_buffer[8] = {1, 2, 3, 4, 5, 6, 7, 8};
				alignas(Align) uint8_t dst_buffer[8]{};
			};

			Data data;

			try
			{
				base::console.WriteLine(base::ToHexString(data.src_buffer));
				base::console.WriteLine(base::ToHexString(data.dst_buffer));
				memory_dma.Copy(data.src_buffer, data.src_buffer + sizeof(data.src_buffer), data.dst_buffer);

				for (size_t i = 0; i < sizeof(data.dst_buffer); i++)
				{
					base::console.Write(std::to_string(data.dst_buffer[i]));
					base::console.Write(", ");
				}

				base::console.WriteLine();
			}
			catch (std::exception const &e)
			{
				base::console.WriteError(CODE_POS_STR + e.what());
			}
			catch (...)
			{
				base::console.WriteError(CODE_POS_STR + "未知异常。");
			}
		}

	} // namespace test
} // namespace base
