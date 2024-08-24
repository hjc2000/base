#include "ChXFilter.h"

#if HAS_THREAD
#include <iostream>
#endif

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

#if HAS_THREAD
void base::Test_ChXFilter()
{
    double x = 15;
    base::ChXFilter filter{
        base::ChXFilter_KError{10},
        base::ChXFilter_FeedbackDiv{1000},
    };

    std::cout << "惯性时间常数 = " << filter.TimeConstant(0.002) << std::endl;

    for (int i = 0; i < 500; i++)
    {
        std::cout << filter.Input(x) << std::endl;
    }
}
#endif
