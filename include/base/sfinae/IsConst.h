#pragma once

namespace base
{
	template <typename T>
	struct IsConst
	{
		static consteval bool Value()
		{
			return false;
		}
	};

	template <typename T>
	struct IsConst<T const>
	{
		static consteval bool Value()
		{
			return true;
		}
	};

	template <typename T>
	consteval bool IsConstType()
	{
		return IsConst<T>::Value();
	}
}
