#include "base/math/Fraction.h"
#include "base/math/Pow.h"
#include "base/wrapper/number-wrapper.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include <stdlib.h>

int main()
{
	std::cout << base::IntPow(2, 2) << std::endl;
	base::Fraction f{base::Double{std::numbers::pi}};
	std::cout << f << std::endl;
	std::cout << static_cast<double>(f) << std::endl;
}
