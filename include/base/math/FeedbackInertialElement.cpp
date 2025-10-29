#include "FeedbackInertialElement.h"
#include <base/math/InertialElement.h>
#include <iostream>

#if HAS_THREAD

void base::Test_ChXFilter()
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

	base::InertialElement<double> inertial_filter{
		filter.TimeConstant(sapmle_interval),
		sapmle_interval,
		0.001,
	};

	for (int i = 0; i < 500; i++)
	{
		std::cout << inertial_filter.Input(x) << std::endl;
	}
}

#endif // HAS_THREAD
