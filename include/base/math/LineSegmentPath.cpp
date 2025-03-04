#include "LineSegmentPath.h"
#include "base/string/define.h"
#include <stdexcept>

base::LineSegmentPath::LineSegmentPath(base::List<std::string> const &points)
{
	if (points.Count() < 2)
	{
		throw std::invalid_argument{CODE_POS_STR + "必须至少有 2 个点，并且第一个点和最后一个点必须是端点。"};
	}

	for (std::string const &point : points)
	{
		AddPoint(point);
	}
}

base::LineSegmentPath::LineSegmentPath(std::initializer_list<std::string> const &points)
{
	if (points.size() < 2)
	{
		throw std::invalid_argument{CODE_POS_STR + "必须至少有 2 个点，并且第一个点和最后一个点必须是端点。"};
	}

	for (std::string const &point : points)
	{
		AddPoint(point);
	}
}

base::List<std::string> const &base::LineSegmentPath::Points() const
{
	return _points;
}

bool base::LineSegmentPath::AddPoint(std::string const &point)
{
	if (_points.Contains(point))
	{
		return false;
	}

	_points.Add(point);
	return true;
}
