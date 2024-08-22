#include "InertialElement.h"

base::InertialElement::InertialElement(InertialElement_TimeConstant const &inertial_time_constant,
                                       InertialElement_SampleInterval const &sample_interval)
{
    _inertial_time_constant = inertial_time_constant.Value();
    _sample_interval = sample_interval.Value();

    _kx = _sample_interval / (_inertial_time_constant + _sample_interval);
    _ky = _inertial_time_constant / (_inertial_time_constant + _sample_interval);
}
