#include "TestFeedbackInertialElement.h" // IWYU pragma: keep
#include "base/math/FeedbackInertialElement.h"
#include <iostream>

void base::test::TestFeedbackInertialElement()
{
	double x = 15;
	double sapmle_interval = 0.002;

	std::cout << "测试 FeedbackInertialElement" << std::endl;

	base::FeedbackInertialElement<double> filter{
		10,
		1000,
	};

	std::cout << "惯性时间常数 = " << filter.TimeConstant(sapmle_interval) << std::endl;

	for (int i = 0; i < 500; i++)
	{
		std::cout << filter.Input(x) << std::endl;
	}

	std::cout << "\n\n"
			  << std::endl;

	std::cout << "测试 InertialElement" << std::endl;
}
