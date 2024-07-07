#pragma once

namespace base
{
	class IUnsubscribeToken
	{
	public:
		virtual ~IUnsubscribeToken() = default;

		virtual void Unsubscribe() = 0;
	};
} // namespace base
