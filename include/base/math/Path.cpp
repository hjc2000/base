#include "Path.h"
#include "base/container/List.h"
#include "base/container/Set.h"
#include <cstdint>

base::math::Path::Path(base::List<base::math::Point> const &points)
{
	for (base::math::Point const &point : points)
	{
		AddPoint(point);
	}
}

base::math::Path::Path(std::initializer_list<base::math::Point> const &points)
{
	for (base::math::Point const &point : points)
	{
		AddPoint(point);
	}
}

base::List<base::math::Point> const &base::math::Path::Points() const
{
	return _points;
}

base::Set<base::math::Point> base::math::Path::PointSet() const
{
	base::Set<base::math::Point> ret;
	for (base::math::Point const &point : _points)
	{
		ret.Add(point);
	}

	return ret;
}

int32_t base::math::Path::PointsCount() const
{
	return _points.Count();
}

bool base::math::Path::AddPoint(base::math::Point const &point)
{
	if (_points.Contains(point))
	{
		return false;
	}

	_points.Add(point);
	return true;
}

bool base::math::Path::RemovePoint(base::math::Point const &point)
{
	return _points.Remove(point);
}

bool base::math::Path::ContainsPoint(base::math::Point const &point) const
{
	return _points.Contains(point);
}

bool base::math::Path::ContainsAllPoints(base::List<base::math::Point> const &points) const
{
	for (auto &point : points)
	{
		if (!ContainsPoint(point))
		{
			return false;
		}
	}

	return true;
}

base::math::Path base::math::Path::operator&(base::math::Path const &another_path) const
{
	base::math::Path ret;
	for (base::math::Point const &point : _points)
	{
		if (another_path.Points().Contains(point))
		{
			ret._points.Add(point);
		}
	}

	return ret;
}

std::string base::math::Path::ToString() const
{
	base::math::Point ret;
	for (int32_t i = 0; i < _points.Count(); i++)
	{
		ret += _points[i];
		if (i < _points.Count() - 1)
		{
			ret += "->";
		}
	}

	return ret;
}

std::shared_ptr<base::IEnumerator<base::math::Point const>> base::math::Path::GetEnumerator()
{
	return const_cast<base::math::Path const &>(*this)._points.GetEnumerator();
}
