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
		};

	} // namespace flash
} // namespace base
