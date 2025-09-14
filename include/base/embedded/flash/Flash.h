#pragma once
#include "flash_handle.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace flash
	{
		class Flash
		{
		private:
			std::shared_ptr<base::flash::flash_handle> _handle;

		public:
			Flash(uint32_t id)
			{
				_handle = base::flash::open(id);
			}

			void Initialize()
			{
				base::flash::initialize(*_handle);
			}

			int64_t SectorSize() const
			{
				return base::flash::sector_size(*_handle);
			}

			int64_t SectorCount() const
			{
				return base::flash::sector_count(*_handle);
			}

			int64_t ReadingSize() const
			{
				return base::flash::reading_size(*_handle);
			}

			int64_t ProgrammingSize() const
			{
				return base::flash::programming_size(*_handle);
			}

			void EraseSector(int64_t sector_index)
			{
				base::flash::erase_sector(*_handle, sector_index);
			}

			void ReadSector(int64_t sector_index,
							int64_t offset,
							base::Span const &span)
			{
				base::flash::read_sector(*_handle,
										 sector_index,
										 offset,
										 span);
			}

			void ProgramSector(int64_t sector_index,
							   int64_t offset,
							   base::ReadOnlySpan const &span)
			{
				base::flash::program_sector(*_handle,
											sector_index,
											offset,
											span);
			}
		};

	} // namespace flash
} // namespace base
