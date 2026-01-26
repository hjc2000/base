#include "base/math/Fraction.h"
#include "base/math/math.h"
#include "base/unit/Hour.h"
#include "base/unit/J.h"
#include "base/unit/kW.h"
#include "base/unit/mA.h"
#include "base/unit/mAh.h"
#include "base/unit/mWh.h"
#include "base/unit/Second.h"
#include "base/unit/V.h"
#include "base/unit/W.h"
#include <iostream>

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
		base::unit::kW kw = v * ma;
		base::unit::J j = kw * base::unit::Second{1};
		base::unit::mWh mwh = j;
		base::unit::mAh mah{ma * base::unit::Hour{1}};
		std::cout << w << std::endl;
		std::cout << kw << std::endl;
		std::cout << (w / v) << std::endl;
		std::cout << (w / ma) << std::endl;
		std::cout << j << std::endl;
		std::cout << mwh << std::endl;
		std::cout << mah << std::endl;
	}

	return 0;
}
