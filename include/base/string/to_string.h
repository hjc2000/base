#pragma once
#include <chrono>
#include <string>

namespace base
{
	inline std::string to_string(std::chrono::nanoseconds const &value)
	{
		return std::string{std::to_string(value.count()) + " ns"};
	}

	inline std::string to_string(std::chrono::microseconds const &value)
	{
		return std::string{std::to_string(value.count()) + " us"};
	}

	inline std::string to_string(std::chrono::milliseconds const &value)
	{
		return std::string{std::to_string(value.count()) + " ms"};
	}

	inline std::string to_string(std::chrono::seconds const &value)
	{
		return std::string{std::to_string(value.count()) + " s"};
	}

	inline std::string to_string(std::chrono::minutes const &value)
	{
		return std::string{std::to_string(value.count()) + " minute"};
	}

	inline std::string to_string(std::chrono::hours const &value)
	{
		return std::string{std::to_string(value.count()) + " h"};
	}

} // namespace base
