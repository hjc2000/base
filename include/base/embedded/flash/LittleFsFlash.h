#pragma once
#include "base/embedded/flash/littlefs/src/lfs.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "Flash.h"
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace base
{
	namespace flash
	{
		class LittleFsFlash
		{
		private:
			class handle_context
			{
			public:
				handle_context(LittleFsFlash *self)
					: _self(self)
				{
				}

				lfs_config _config{};
				LittleFsFlash *_self = nullptr;
			};

			handle_context _handle_context{this};
			std::shared_ptr<base::flash::Flash> _flash;

			int Erase(lfs_block_t block)
			{
				return 0;
			}

			int Read(lfs_block_t block,
					 lfs_off_t off,
					 void *buffer,
					 lfs_size_t size)
			{
				base::Span span{reinterpret_cast<uint8_t *>(buffer), size};
				_flash->ReadSector(block, off, span);
				return 0;
			}

			int Program(lfs_block_t block,
						lfs_off_t off,
						void const *buffer,
						lfs_size_t size)
			{
				return 0;
			}

			void InitializeFunctionPtr();

		public:
			LittleFsFlash(std::shared_ptr<base::flash::Flash> const &flash)
			{
				if (flash == nullptr)
				{
					throw std::invalid_argument{CODE_POS_STR + "不允许传入空指针。"};
				}

				_flash = flash;
				InitializeFunctionPtr();
			}
		};

	} // namespace flash
} // namespace base
