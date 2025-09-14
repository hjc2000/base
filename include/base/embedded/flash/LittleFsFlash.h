#pragma once
#include "base/embedded/flash/littlefs/src/lfs.h"

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

			int Erase(lfs_block_t block)
			{
				return 0;
			}

			int Read(lfs_block_t block,
					 lfs_off_t off,
					 void *buffer,
					 lfs_size_t size)
			{
				return 0;
			}

			int Program(lfs_block_t block,
						lfs_off_t off,
						void const *buffer,
						lfs_size_t size)
			{
				return 0;
			}

			void InitializeFunctionPtr()
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
					return 0;
				};
			}

		public:
			LittleFsFlash()
			{
			}
		};

	} // namespace flash
} // namespace base
