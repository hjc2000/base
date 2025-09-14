#pragma once
#include "base/container/Range.h"
#include "base/stream/Span.h"
#include <cstdint>
#include <memory>

namespace base
{
	namespace flash
	{
		class RamFlash
		{
		private:
			int64_t _sector_size{256};
			int64_t _sector_count{100};
			int64_t _reading_size{4};
			int64_t _programming_size{8};
			std::unique_ptr<uint8_t[]> _buffer;
			base::Span _span{};

		public:
			RamFlash(int64_t sector_size,
					 int64_t sector_count)
			{
				_sector_size = sector_size;
				_sector_count = sector_count;
				_buffer = std::unique_ptr<uint8_t[]>{new uint8_t[sector_size * sector_count]};
				_span = base::Span{_buffer.get(), sector_size * sector_count};
				_span.FillWith(0xff);
			}

			void Initialize()
			{
			}

			int64_t SectorSize() const
			{
				return _sector_size;
			}

			int64_t SectorCount() const
			{
				return _sector_count;
			}

			int64_t ReadingSize() const
			{
				return _reading_size;
			}

			int64_t ProgrammingSize() const
			{
				return _programming_size;
			}

			void EraseSector(int64_t sector_index)
			{
				base::Range range{
					sector_index * _sector_size,
					_sector_size,
				};

				_span[range].FillWith(0xff);
			}

			void ReadSector(int64_t sector_index,
							int64_t offset,
							base::Span const &span)
			{
				base::Range range{
					sector_index * _sector_size + offset,
					_sector_size,
				};

				span.CopyFrom(_span[range]);
			}

			void ProgramSector(int64_t sector_index,
							   int64_t offset,
							   base::ReadOnlySpan const &span)
			{
				base::Range range{
					sector_index * _sector_size + offset,
					_sector_size,
				};

				_span[range].CopyFrom(span);
			}
		};

	} // namespace flash
} // namespace base
