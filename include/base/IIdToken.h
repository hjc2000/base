#pragma once
#include <cstdint>
#include <memory>

namespace base
{
	///
	/// @brief 基于 ID 的令牌。
	///
	///
	class IIdToken
	{
	public:
		///
		/// @brief 本令牌对象的提供者。
		///
		/// @return void*
		///
		virtual void *Provider() const = 0;

		///
		/// @brief 令牌 ID.
		///
		/// @return uint64_t
		///
		virtual uint64_t ID() const = 0;
	};

	using SpIIdToken = std::shared_ptr<base::IIdToken>;

} // namespace base
