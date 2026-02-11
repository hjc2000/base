#pragma once
#include <exception>

namespace base::flash
{
	class SectorIndexOutOfRangeException :
		public std::exception
	{
	public:
		virtual char const *what() const noexcept override
		{
			return "扇区索引超出范围。";
		}
	};

	class CrossSectorException :
		public std::exception
	{
	public:
		virtual char const *what() const noexcept override
		{
			return "不能跨扇区。";
		}
	};

	class AlignmentException :
		public std::exception
	{
	public:
		virtual char const *what() const noexcept override
		{
			return "对齐异常。";
		}
	};

} // namespace base::flash
