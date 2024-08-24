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
