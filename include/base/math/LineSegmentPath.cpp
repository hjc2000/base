#include "LineSegmentPath.h"
#include "base/string/define.h"
#include <stdexcept>

base::LineSegmentPath::LineSegmentPath(base::List<std::string> const &points)
	: _points(points)
{
	if (_points.Count() < 2)
	{
		throw std::invalid_argument{CODE_POS_STR + "必须至少有 2 个点，并且第一个点和最后一个点必须是端点。"};
	}
}

base::List<std::string> const &base::LineSegmentPath::Points() const
{
	return _points;
}
