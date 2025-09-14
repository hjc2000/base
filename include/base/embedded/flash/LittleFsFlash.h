#pragma once
#include "base/embedded/flash/exception.h"
#include "base/embedded/flash/littlefs/src/lfs.h"
#include "base/stream/ReadOnlySpan.h"
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

			int Erase(lfs_block_t block) noexcept
			{
				try
				{
					_flash->EraseSector(block);
					return 0;
				}
				catch (base::flash::SectorIndexOutOfRangeException &e)
				{
					return lfs_error::LFS_ERR_INVAL;
				}
				catch (...)
				{
					return lfs_error::LFS_ERR_IO;
				}
			}

			int Read(lfs_block_t block,
					 lfs_off_t off,
					 void *buffer,
					 lfs_size_t size) noexcept
			{
				try
				{
					base::Span span{reinterpret_cast<uint8_t *>(buffer), size};
					_flash->ReadSector(block, off, span);
					return 0;
				}
				catch (base::flash::SectorIndexOutOfRangeException &e)
				{
					return lfs_error::LFS_ERR_INVAL;
				}
				catch (base::flash::CrossSectorException &e)
				{
					return lfs_error::LFS_ERR_INVAL;
				}
				catch (base::flash::AlignmentException &e)
				{
					return lfs_error::LFS_ERR_INVAL;
				}
				catch (...)
				{
					return lfs_error::LFS_ERR_IO;
				}
			}

			int Program(lfs_block_t block,
						lfs_off_t off,
						void const *buffer,
						lfs_size_t size) noexcept
			{
				try
				{
					base::ReadOnlySpan span{reinterpret_cast<uint8_t const *>(buffer), size};
					_flash->ProgramSector(block, off, span);
					return 0;
				}
				catch (base::flash::SectorIndexOutOfRangeException &e)
				{
					return lfs_error::LFS_ERR_INVAL;
				}
				catch (base::flash::CrossSectorException &e)
				{
					return lfs_error::LFS_ERR_INVAL;
				}
				catch (base::flash::AlignmentException &e)
				{
					return lfs_error::LFS_ERR_INVAL;
				}
				catch (...)
				{
					return lfs_error::LFS_ERR_IO;
				}
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
