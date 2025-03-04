#include "Path.h"

base::math::Path::Path(base::List<std::string> const &points)
{
	for (std::string const &point : points)
	{
		AddPoint(point);
	}
}

base::math::Path::Path(std::initializer_list<std::string> const &points)
{
	for (std::string const &point : points)
	{
		AddPoint(point);
	}
}

base::List<std::string> const &base::math::Path::Points() const
{
	return _points;
}

bool base::math::Path::AddPoint(std::string const &point)
{
	if (_points.Contains(point))
	{
		return false;
	}

	_points.Add(point);
	return true;
}

bool base::math::Path::RemovePoint(std::string const &point)
{
	return _points.Remove(point);
}

bool base::math::Path::ContainsPoint(std::string const &point) const
{
	return _points.Contains(point);
}

base::math::Path base::math::Path::IntersectionPoints(base::math::Path const &another_path) const
{
	base::math::Path ret;
	for (std::string const &point : _points)
	{
		if (another_path.Points().Contains(point))
		{
			ret._points.Add(point);
		}
	}

	return ret;
}

base::math::Path base::math::Path::operator&(base::math::Path const &another_path) const
{
	return IntersectionPoints(another_path);
}
