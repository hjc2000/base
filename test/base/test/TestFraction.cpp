#include "TestFraction.h"
#include "base/math/Fraction.h"
#include "base/string/define.h"
#include <cstdint>
#include <iostream>
#include <limits>
#include <numbers>

#if HAS_THREAD

void base::test::TestFraction()
{
	{
		std::cout << std::endl
				  << CODE_POS_STR;

		base::Fraction f{std::numbers::pi};
		constexpr int precision = 512;

		std::cout << "分数: " << f << std::endl;

		std::cout << "std::numbers::pi: \t\t"
				  << std::setprecision(precision)
				  << std::numbers::pi
				  << std::endl;

		std::cout << "分数表示的 pi 转为 double: \t"
				  << std::setprecision(precision)
				  << static_cast<double>(f)
				  << std::endl;

		std::cout << "误差: "
				  << std::setprecision(precision)
				  << static_cast<double>(f) - std::numbers::pi
				  << std::endl;

		f.ReduceResolution(base::Fraction{1, std::numeric_limits<int64_t>::max()});
		std::cout << "降低分辨率后的分数: " << f << std::endl;
	}

	{
		std::cout << std::endl
				  << CODE_POS_STR;

		float f_pi = static_cast<float>(std::numbers::pi);
		base::Fraction f{f_pi};
		constexpr int precision = 512;

		std::cout << "分数: " << f << std::endl;

		std::cout << "f_pi: \t\t"
				  << std::setprecision(precision)
				  << f_pi
				  << std::endl;

		std::cout << "分数表示的 pi 转为 float: \t"
				  << std::setprecision(precision)
				  << static_cast<float>(f)
				  << std::endl;

		std::cout << "误差: "
				  << std::setprecision(precision)
				  << static_cast<float>(f) - f_pi
				  << std::endl;

		f.ReduceResolution(base::Fraction{1, std::numeric_limits<int64_t>::max()});
		std::cout << "降低分辨率后的分数: " << f << std::endl;
	}
}

#endif // HAS_THREAD
