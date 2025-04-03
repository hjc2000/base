#include "base/math/Fraction.h"
#include "base/wrapper/number-wrapper.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

int main()
{
	base::Fraction f{base::Double{0.5}};
	std::cout << f << std::endl;
}
