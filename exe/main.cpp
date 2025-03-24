#include "base/time/DateTime.h"
#include <cstdlib>
#include <iostream>
#include <stdlib.h>

class Test
{
public:
	Test()
	{
		std::cout << "构造" << std::endl;
	}
};

void test_func()
{
	std::cout << "第一条语句" << std::endl;
	static Test test;
}

int main()
{
	test_func();
	test_func();
}
