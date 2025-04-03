#include "base/bit/bit.h"
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

int main()
{
	uint64_t reg = 0;
	base::bit::SetBit(reg, 1);
	std::cout << reg << std::endl;
	base::bit::ResetBit(reg, 1);
	std::cout << reg << std::endl;
	std::cout << base::bit::BitMask(0, 2) << std::endl;
}
