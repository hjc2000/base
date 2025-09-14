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

			void InitializeBuffer()
			{
				_buffer = std::unique_ptr<uint8_t[]>{new uint8_t[_sector_size * _sector_count]};
				_span = base::Span{_buffer.get(), _sector_size * _sector_count};
				_span.FillWith(0xff);
			}

		public:
			RamFlash()
			{
				InitializeBuffer();
			}

			RamFlash(int64_t sector_size,
					 int64_t sector_count,
					 int64_t reading_size,
					 int64_t programming_size)
			{

				_sector_size = sector_size;
				_sector_count = sector_count;
				_reading_size = reading_size;
				_programming_size = programming_size;
				InitializeBuffer();
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
				try
				{
					base::Range range{
						sector_index * _sector_size,
						(sector_index + 1) * _sector_size,
					};

					_span[range].FillWith(0xff);
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
				}
			}

			void ReadSector(int64_t sector_index,
							int64_t offset,
							base::Span const &span)
			{
				try
				{
					int64_t begin = sector_index * _sector_size + offset;

					int64_t end = std::min<int64_t>((sector_index + 1) * _sector_size,
													begin + span.Size());

					base::Range range{begin, end};
					span.CopyFrom(_span[range]);
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
				}
			}

			void ProgramSector(int64_t sector_index,
							   int64_t offset,
							   base::ReadOnlySpan const &span)
			{
				try
				{
					int64_t begin = sector_index * _sector_size + offset;

					int64_t end = std::min<int64_t>((sector_index + 1) * _sector_size,
													begin + span.Size());

					base::Range range{begin, end};
					_span[range].CopyFrom(span);
				}
				catch (std::exception const &e)
				{
					throw std::runtime_error{CODE_POS_STR + e.what()};
				}
				catch (...)
				{
					throw std::runtime_error{CODE_POS_STR + "未知的异常。"};
				}
			}
		};

	} // namespace flash
} // namespace base
