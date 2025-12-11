#include "base/math/BigInteger.h"
#include "base/math/math.h"
#include "base/test/test_ertec200p_3_timing_provider.h"
#include "base/test/TestCircleDeque.h"
#include "base/test/TestFactorExtractor.h"
#include "base/test/TestFraction.h"
#include "base/test/TestInertialElement.h"
#include "base/test/TestParse.h"
#include "base/test/TestUtf8Reader.h"
#include <cstdint>
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
	base::test::TestFraction();
	// constexpr int64_t gcd = base::gcd(16, 4);
	// std::cout << gcd << std::endl;
	return 0;
}
