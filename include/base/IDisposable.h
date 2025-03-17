#pragma once
#include <base/pch.h>

namespace base
{
	class IDisposable
	{
	public:
		virtual void Dispose() = 0;
	};
} // namespace base
