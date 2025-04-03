#include "base/math/Fraction.h"
#include "base/wrapper/number-wrapper.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include <stdlib.h>

int main()
{
	base::Fraction f{base::Double{std::numbers::pi}};
	std::cout << f << std::endl;
}
