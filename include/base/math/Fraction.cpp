#include "Fraction.h" // IWYU pragma: keep

std::string base::Fraction::ToString() const
{
	return std::to_string(_num) + " / " + std::to_string(_den);
}

namespace
{
	base::Fraction _pi{
		static_cast<uint64_t>(884279719003555),
		static_cast<uint64_t>(281474976710656),
	};

}

base::Fraction base::constant::PI()
{
	return _pi;
}

std::string std::to_string(boost::multiprecision::cpp_int const &value)
{
	boost::multiprecision::cpp_int temp = value;
	bool is_negative = temp < 0;
	std::string ret;
	if (temp < 0)
	{
		temp = -temp;
	}

	while (temp > 0)
	{
		uint8_t num = static_cast<uint8_t>(temp % 10);
		ret = std::to_string(num) + ret;
		temp /= 10;
	}

	if (is_negative)
	{
		ret = '-' + ret;
	}

	return ret;
}
