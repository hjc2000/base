#include "ChXFilter.h"

base::ChXFilter::ChXFilter(ChXFilter_KError const &k_error, ChXFilter_FeedbackDiv const &feedback_div)
{
	_k_error = k_error.Value();
	_feedback_div = feedback_div.Value();
}

double base::ChXFilter::Input(double x)
{
	double error = x - Feedback();
	_current_output += error * _k_error;
	return Feedback();
}

double base::ChXFilter::TimeConstant(double sample_interval)
{
	/* 		k_error = (sample_interval * k) / T1
	 *	 	k_error = sample_interval * (k / T1)
	 *
	 * 则
	 * 		k / T1 = k_error / sample_interval
	 * 		T1 / k = sample_interval / k_error
	 *
	 * 惯性时间常数为
	 *		T1 / (k * kb)
	 * 		= (T1 / k) / kb
	 * 		= (T1 / k) * feedback_div
	 * 		= sample_interval / k_error * feedback_div
	 */
	return sample_interval * _feedback_div / _k_error;
}

#if HAS_THREAD

	#include <base/math/InertialElement.h>
	#include <iostream>

void base::Test_ChXFilter()
{
	double x = 15;
	double sapmle_interval = 0.002;

	std::cout << "测试 ChXFilter" << std::endl;

	base::ChXFilter filter{
		base::ChXFilter_KError{10},
		base::ChXFilter_FeedbackDiv{1000},
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
		base::InertialElement<double>::TimeConstant{filter.TimeConstant(sapmle_interval)},
		base::InertialElement<double>::SampleInterval{sapmle_interval},
	};

	for (int i = 0; i < 500; i++)
	{
		std::cout << inertial_filter.Input(x) << std::endl;
	}
}
#endif
