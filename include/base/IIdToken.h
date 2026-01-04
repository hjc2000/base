#pragma once
#include <cstdint>
#include <memory>

namespace base
{
	///
	/// @brief 基于 ID 的令牌。
	///
	class IIdToken
	{
	public:
		virtual ~IIdToken() = default;

		///
		/// @brief 本令牌对象的提供者。
		///
		/// @return
		///
		virtual void *Provider() const = 0;

		///
		/// @brief 令牌 ID.
		///
		/// @return
		///
		virtual uint64_t ID() const = 0;
	};

	using SpIIdToken = std::shared_ptr<base::IIdToken>;

} // namespace base
