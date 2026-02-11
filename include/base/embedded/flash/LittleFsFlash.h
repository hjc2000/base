#pragma once
#include "base/Console.h"
#include "base/embedded/flash/exception.h"
#include "base/embedded/flash/littlefs/src/lfs.h"
#include "base/stream/ReadOnlySpan.h"
#include "base/stream/Span.h"
#include "base/string/define.h"
#include "Flash.h"
#include <cstdint>
#include <exception>
#include <numeric>
#include <stdexcept>

namespace base::flash
{
	///
	/// @brief 通过 littlefs 接管 flash.
	///
	class LittleFsFlash
	{
	private:
		class lfs_config_context
		{
		public:
			lfs_config_context(LittleFsFlash *self)
				: _self(self)
			{
			}

			lfs_config _config{};
			LittleFsFlash *_self = nullptr;
		};

		lfs_t _lfs{};
		lfs_config_context _lfs_config_context{this};
		base::flash::Flash _flash;

		int Erase(lfs_block_t block) noexcept
		{
			try
			{
				_flash.EraseSector(block);
				return 0;
			}
			catch (base::flash::SectorIndexOutOfRangeException &e)
			{
				base::console().WriteLine(CODE_POS_STR + "SectorIndexOutOfRangeException");
				return lfs_error::LFS_ERR_INVAL;
			}
			catch (std::exception const &e)
			{
				base::console().WriteLine(CODE_POS_STR + e.what());
				return lfs_error::LFS_ERR_IO;
			}
			catch (...)
			{
				base::console().WriteLine(CODE_POS_STR + "未知异常。");
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
				_flash.ReadSector(block, off, span);
				return 0;
			}
			catch (base::flash::SectorIndexOutOfRangeException &e)
			{
				base::console().WriteLine(CODE_POS_STR + "SectorIndexOutOfRangeException");
				return lfs_error::LFS_ERR_INVAL;
			}
			catch (base::flash::CrossSectorException &e)
			{
				base::console().WriteLine(CODE_POS_STR + "CrossSectorException");
				return lfs_error::LFS_ERR_INVAL;
			}
			catch (base::flash::AlignmentException &e)
			{
				base::console().WriteLine(CODE_POS_STR + "AlignmentException");
				return lfs_error::LFS_ERR_INVAL;
			}
			catch (std::exception const &e)
			{
				base::console().WriteLine(CODE_POS_STR + e.what());
				return lfs_error::LFS_ERR_IO;
			}
			catch (...)
			{
				base::console().WriteLine(CODE_POS_STR + "未知异常。");
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
				_flash.ProgramSector(block, off, span);
				return 0;
			}
			catch (base::flash::SectorIndexOutOfRangeException &e)
			{
				base::console().WriteLine(CODE_POS_STR + "SectorIndexOutOfRangeException");
				return lfs_error::LFS_ERR_INVAL;
			}
			catch (base::flash::CrossSectorException &e)
			{
				base::console().WriteLine(CODE_POS_STR + "CrossSectorException");
				return lfs_error::LFS_ERR_INVAL;
			}
			catch (base::flash::AlignmentException &e)
			{
				base::console().WriteLine(CODE_POS_STR + "AlignmentException");
				return lfs_error::LFS_ERR_INVAL;
			}
			catch (std::exception const &e)
			{
				base::console().WriteLine(CODE_POS_STR + e.what());
				return lfs_error::LFS_ERR_IO;
			}
			catch (...)
			{
				base::console().WriteLine(CODE_POS_STR + "未知异常。");
				return lfs_error::LFS_ERR_IO;
			}
		}

		void InitalizeAttributes()
		{
			_lfs_config_context._config.read_size = _flash.ReadingSize();
			_lfs_config_context._config.prog_size = _flash.ProgrammingSize();
			_lfs_config_context._config.block_size = _flash.SectorSize();
			_lfs_config_context._config.block_count = _flash.SectorCount();
			_lfs_config_context._config.block_cycles = 1000;
			_lfs_config_context._config.cache_size = std::lcm<int64_t>(_flash.ReadingSize(), _flash.ProgrammingSize());

			if (_flash.SectorSize() % _lfs_config_context._config.cache_size != 0)
			{
				throw std::runtime_error{CODE_POS_STR + "缓存大小不是扇区大小的因数。"};
			}

			_lfs_config_context._config.lookahead_size = 256;
		}

		void InitializeFunctionPtr()
		{
			_lfs_config_context._config.erase = [](lfs_config const *c, lfs_block_t block) -> int
			{
				LittleFsFlash *self = reinterpret_cast<lfs_config_context const *>(c)->_self;
				return self->Erase(block);
			};

			_lfs_config_context._config.read = [](lfs_config const *c,
												  lfs_block_t block,
												  lfs_off_t off,
												  void *buffer,
												  lfs_size_t size) -> int
			{
				LittleFsFlash *self = reinterpret_cast<lfs_config_context const *>(c)->_self;
				return self->Read(block, off, buffer, size);
			};

			_lfs_config_context._config.prog = [](lfs_config const *c,
												  lfs_block_t block,
												  lfs_off_t off,
												  void const *buffer,
												  lfs_size_t size) -> int
			{
				LittleFsFlash *self = reinterpret_cast<lfs_config_context const *>(c)->_self;
				return self->Program(block, off, buffer, size);
			};

			_lfs_config_context._config.sync = [](lfs_config const *c) -> int
			{
				return lfs_error::LFS_ERR_OK;
			};
		}

	public:
		LittleFsFlash(base::flash::Flash const &flash)
			: _flash(flash)
		{
			InitalizeAttributes();
			InitializeFunctionPtr();
		}

		///
		/// @brief 挂载文件系统.
		///
		///
		void Mount()
		{
			int result = lfs_mount(&_lfs, &_lfs_config_context._config);
			if (result == lfs_error::LFS_ERR_OK)
			{
				base::console().WriteLine("挂载成功。");
				return;
			}

			// 首次挂载失败
			base::console().WriteLine("挂载失败，格式化后重试。");
			Format();
			result = lfs_mount(&_lfs, &_lfs_config_context._config);
			if (result != lfs_error::LFS_ERR_OK)
			{
				throw std::runtime_error{CODE_POS_STR + "格式化后重试挂载失败。"};
			}

			base::console().WriteLine("挂载成功。");
		}

		///
		/// @brief 卸载文件系统。
		///
		///
		void Unmount()
		{
			int result = lfs_unmount(&_lfs);
			if (result != lfs_error::LFS_ERR_OK)
			{
				throw std::runtime_error{CODE_POS_STR + "卸载文件系统失败。"};
			}
		}

		///
		/// @brief 重新挂载文件系统。
		///
		void Remount()
		{
			Unmount();
			Mount();
		}

		///
		/// @brief 格式化文件系统。
		///
		void Format()
		{
			int result = lfs_format(&_lfs, &_lfs_config_context._config);
			if (result != lfs_error::LFS_ERR_OK)
			{
				throw std::runtime_error{CODE_POS_STR + "格式化失败。"};
			}
		}

		///
		/// @brief 打开或创建文件。
		///
		/// @note 如果文件存在则直接打开，如果文件不存在，则创建后打开。
		///
		/// @param file
		/// @param path
		///
		void OpenOrCreateFile(lfs_file_t &file, char const *path)
		{
			int result = lfs_file_open(&_lfs,
									   &file,
									   path,
									   lfs_open_flags::LFS_O_RDWR | lfs_open_flags::LFS_O_CREAT);

			if (result != lfs_error::LFS_ERR_OK)
			{
				throw std::runtime_error{CODE_POS_STR + "打开或创建文件失败。"};
			}
		}

		///
		/// @brief 获取指定文件的文件指针。
		///
		/// @param file
		/// @return
		///
		int64_t GetFilePosition(lfs_file_t &file)
		{
			lfs_soff_t result = lfs_file_tell(&_lfs, &file);

			if (result < 0)
			{
				throw std::runtime_error{CODE_POS_STR + "获取文件指针失败。"};
			}

			return result;
		}

		///
		/// @brief 设置指定文件的文件指针。
		///
		/// @param file
		/// @param position
		///
		void SetFilePosition(lfs_file_t &file, int64_t position)
		{
			lfs_soff_t result = lfs_file_seek(&_lfs, &file, 0, lfs_whence_flags::LFS_SEEK_SET);
			if (result < 0)
			{
				throw std::runtime_error{CODE_POS_STR + "设置文件指针失败。"};
			}
		}

		///
		/// @brief 获取指定文件的大小。
		///
		/// @param file
		/// @return
		///
		int64_t GetFileSize(lfs_file_t &file)
		{
			int64_t result = lfs_file_size(&_lfs, &file);
			if (result < 0)
			{
				throw std::runtime_error{CODE_POS_STR + "获取文件大小失败。"};
			}

			return result;
		}

		///
		/// @brief 设置指定文件的大小。
		///
		/// @param file
		/// @param size
		///
		void SetFileSize(lfs_file_t &file, int64_t size)
		{
			int result = lfs_file_truncate(&_lfs, &file, size);
			if (result < 0)
			{
				throw std::runtime_error{CODE_POS_STR + "设置文件大小失败。"};
			}
		}

		///
		/// @brief 读取指定文件。
		///
		/// @param file
		/// @param span
		/// @return
		///
		int64_t ReadFile(lfs_file_t &file, base::Span const &span)
		{
			int64_t have_read = lfs_file_read(&_lfs, &file, span.Buffer(), span.Size());
			if (have_read < 0)
			{
				throw std::runtime_error{CODE_POS_STR + "读取文件失败。"};
			}

			return have_read;
		}

		///
		/// @brief 写入指定文件。
		///
		/// @param file
		/// @param span
		///
		void WriteFile(lfs_file_t &file, base::ReadOnlySpan const &span)
		{
			base::ReadOnlySpan remain_span{span};

			int64_t have_written = lfs_file_write(&_lfs,
												  &file,
												  remain_span.Buffer(),
												  remain_span.Size());

			if (have_written < 0)
			{
				throw std::runtime_error{CODE_POS_STR + "写入文件失败。"};
			}

			if (have_written != span.Size())
			{
				throw std::runtime_error{CODE_POS_STR + "写入文件的大小不等于 span 的大小。"};
			}
		}

		///
		/// @brief 关闭指定文件。
		///
		/// @param file
		///
		void CloseFile(lfs_file_t &file)
		{
			// remember the storage is not updated until the file is closed successfully
			int result = lfs_file_close(&_lfs, &file);
			if (result != lfs_error::LFS_ERR_OK)
			{
				throw std::runtime_error{CODE_POS_STR + "关闭文件失败。"};
			}
		}
	};

} // namespace base::flash
