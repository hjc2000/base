#pragma once
#include <cstdint>

namespace base
{
	class IIdToken
	{
	public:
		virtual void *Provider() const = 0;
		virtual uint64_t ID() const = 0;
	};
} // namespace base
