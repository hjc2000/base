#pragma once
#include "Position.h"

namespace base
{
	class PositionRange
	{
	private:
		base::Position _start;
		base::Position _end;

	public:
		PositionRange() = default;

		PositionRange(base::Position const &start, base::Position const &end);

		base::Position Start() const
		{
			return _start;
		}

		base::Position End() const
		{
			return _end;
		}
	};
} // namespace base
