#include "LittleFsFlash.h" // IWYU pragma: keep
#include "base/embedded/flash/exception.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include <cstdint>
#include <numeric>

int base::flash::LittleFsFlash::Erase(lfs_block_t block) noexcept
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

int base::flash::LittleFsFlash::Read(lfs_block_t block,
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

int base::flash::LittleFsFlash::Program(lfs_block_t block,
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

void base::flash::LittleFsFlash::InitalizeAttributes()
{
	_handle_context._config.read_size = _flash->ReadingSize();
	_handle_context._config.prog_size = _flash->ProgrammingSize();
	_handle_context._config.block_size = _flash->SectorSize();
	_handle_context._config.block_count = _flash->SectorCount();
	_handle_context._config.block_cycles = 1000;
	_handle_context._config.cache_size = std::lcm<int64_t>(_flash->ReadingSize(), _flash->ProgrammingSize());

	if (_flash->SectorSize() % _handle_context._config.cache_size != 0)
	{
		throw std::runtime_error{CODE_POS_STR + "缓存大小不是扇区大小的因数。"};
	}

	_handle_context._config.lookahead_size = 256;
}

void base::flash::LittleFsFlash::InitializeFunctionPtr()
{
	_handle_context._config.erase = [](lfs_config const *c, lfs_block_t block) -> int
	{
		LittleFsFlash *self = reinterpret_cast<handle_context const *>(c)->_self;
		return self->Erase(block);
	};

	_handle_context._config.read = [](lfs_config const *c,
									  lfs_block_t block,
									  lfs_off_t off,
									  void *buffer,
									  lfs_size_t size) -> int
	{
		LittleFsFlash *self = reinterpret_cast<handle_context const *>(c)->_self;
		return self->Read(block, off, buffer, size);
	};

	_handle_context._config.prog = [](lfs_config const *c,
									  lfs_block_t block,
									  lfs_off_t off,
									  void const *buffer,
									  lfs_size_t size) -> int
	{
		LittleFsFlash *self = reinterpret_cast<handle_context const *>(c)->_self;
		return self->Program(block, off, buffer, size);
	};

	_handle_context._config.sync = [](lfs_config const *c) -> int
	{
		return lfs_error::LFS_ERR_OK;
	};
}
