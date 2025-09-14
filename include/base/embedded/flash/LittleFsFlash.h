#pragma once
#include "base/embedded/flash/littlefs/src/lfs.h"
#include "Flash.h"

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
			/// @brief 挂载 flash.
			///
			///
			void Mount();

			void OpenOrCreate(lfs_file_t &file, char const *path);
		};

	} // namespace flash
} // namespace base
