#include "base/math/Fraction.h"
#include "base/math/math.h"
#include "base/test/test_ertec200p_3_timing_provider.h"
#include "base/test/TestCircleDeque.h"
#include "base/test/TestFactorExtractor.h"
#include "base/test/TestFraction.h"
#include "base/test/TestInertialElement.h"
#include "base/test/TestParse.h"
#include "base/test/TestUtf8Reader.h"
#include "base/unit/mA.h"
#include "base/unit/V.h"
#include "base/unit/W.h"
#include <cstdint>
#include <iostream>
#include <numbers>

int main()
{
	// base::test::TestCircleDeque();
	// base::test::TestFactorExtractor();
	// base::test::TestParseInt32();
	// base::test::TestParseInt64();
	// base::test::TestParseDouble();
	// base::test::test_ertec200p_3_timing_provider();
	// base::test::TestUtf8Reader();
	// base::test::TestInertialElement();
	// base::test::TestFraction();
	// constexpr int64_t gcd = base::gcd(16, 4);
	// std::cout << gcd << std::endl;

	{
		base::Fraction f{
			662607015,
			base::pow<base::BigInteger>(10, 34 + 8),
		};

		std::cout << f << std::endl;
	}

	{
		base::unit::mA ma{1000};
		base::unit::V v{100};
		base::unit::W w = v * ma;
		std::cout << w << std::endl;
		std::cout << (w / v) << std::endl;
		std::cout << (w / ma) << std::endl;
	}

	return 0;
}
