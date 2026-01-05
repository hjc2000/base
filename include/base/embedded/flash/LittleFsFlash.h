#pragma once
#include "base/embedded/flash/littlefs/src/lfs.h"
#include "Flash.h"
#include <cstdint>

namespace base
{
	namespace flash
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

			int Erase(lfs_block_t block) noexcept;

			int Read(lfs_block_t block,
					 lfs_off_t off,
					 void *buffer,
					 lfs_size_t size) noexcept;

			int Program(lfs_block_t block,
						lfs_off_t off,
						void const *buffer,
						lfs_size_t size) noexcept;

			void InitalizeAttributes();
			void InitializeFunctionPtr();

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
			void Mount();

			///
			/// @brief 卸载文件系统。
			///
			///
			void Unmount();

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
			void Format();

			///
			/// @brief 打开或创建文件。
			///
			/// @note 如果文件存在则直接打开，如果文件不存在，则创建后打开。
			///
			/// @param file
			/// @param path
			///
			void OpenOrCreateFile(lfs_file_t &file, char const *path);

			///
			/// @brief 获取指定文件的文件指针。
			///
			/// @param file
			/// @return
			///
			int64_t GetFilePosition(lfs_file_t &file);

			///
			/// @brief 设置指定文件的文件指针。
			///
			/// @param file
			/// @param position
			///
			void SetFilePosition(lfs_file_t &file, int64_t position);

			///
			/// @brief 获取指定文件的大小。
			///
			/// @param file
			/// @return
			///
			int64_t GetFileSize(lfs_file_t &file);

			///
			/// @brief 设置指定文件的大小。
			///
			/// @param file
			/// @param size
			///
			void SetFileSize(lfs_file_t &file, int64_t size);

			///
			/// @brief 读取指定文件。
			///
			/// @param file
			/// @param span
			/// @return
			///
			int64_t ReadFile(lfs_file_t &file, base::Span const &span);

			///
			/// @brief 写入指定文件。
			///
			/// @param file
			/// @param span
			///
			void WriteFile(lfs_file_t &file, base::ReadOnlySpan const &span);

			///
			/// @brief 关闭指定文件。
			///
			/// @param file
			///
			void CloseFile(lfs_file_t &file);
		};

	} // namespace flash
} // namespace base
