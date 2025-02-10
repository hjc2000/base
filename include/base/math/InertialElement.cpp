#include "InertialElement.h"

base::InertialElement::InertialElement(InertialElement_TimeConstant const &inertial_time_constant,
									   InertialElement_SampleInterval const &sample_interval)
{
	ChangeParameter(inertial_time_constant, sample_interval);
}

double base::InertialElement::Input(double x)
{
	_current_output = _ky * _current_output + _kx * x;
	return _current_output;
}

double base::InertialElement::CurrentOutput() const
{
	return _current_output;
}

void base::InertialElement::SetCurrentOutput(double value)
{
	_current_output = value;
}

void base::InertialElement::ChangeParameter(InertialElement_TimeConstant const &inertial_time_constant)
{
	_inertial_time_constant = inertial_time_constant.Value();
	_kx = _sample_interval / (_inertial_time_constant + _sample_interval);
	_ky = _inertial_time_constant / (_inertial_time_constant + _sample_interval);
}

void base::InertialElement::ChangeParameter(InertialElement_SampleInterval const &sample_interval)
{
	_sample_interval = sample_interval.Value();
	_kx = _sample_interval / (_inertial_time_constant + _sample_interval);
	_ky = _inertial_time_constant / (_inertial_time_constant + _sample_interval);
}

void base::InertialElement::ChangeParameter(InertialElement_TimeConstant const &inertial_time_constant,
											InertialElement_SampleInterval const &sample_interval)
{
	_inertial_time_constant = inertial_time_constant.Value();
	_sample_interval = sample_interval.Value();
	_kx = _sample_interval / (_inertial_time_constant + _sample_interval);
	_ky = _inertial_time_constant / (_inertial_time_constant + _sample_interval);
}
