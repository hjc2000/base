#pragma once
#include <cstdlib>

namespace base
{
	class ExitGuard
	{
	public:
		ExitGuard() = default;

		~ExitGuard()
		{
			exit(0);
		}
	};

} // namespace base
