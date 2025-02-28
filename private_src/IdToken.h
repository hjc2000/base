#pragma once
#include <cstdint>

namespace base
{
	class IdToken
	{
	private:
		uint64_t const _id{};
		bool _used = false;

	public:
		IdToken(uint64_t id);

		IdToken(IdToken const &o) = delete;
		IdToken &operator=(IdToken const &o) = delete;

	public:
		uint64_t ID() const;

		bool Used() const;

		void SetAsUsed();
	};
} // namespace base
