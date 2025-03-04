#include "Path.h"
#include "base/container/List.h"
#include "base/container/Set.h"
#include <cstdint>
#include <iostream>

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

#if HAS_THREAD
	#include <base/math/Combination.h>
	#include <base/math/PathCollection.h>

void base::math::test::test_path()
{
	base::math::PathCollection paths{
		base::math::Path{"A", "B", "D", "G"},
		base::math::Path{"C", "D", "H"},
		base::math::Path{"F", "G", "H"},
		base::math::Path{"A", "C", "F"},
		base::math::Path{"E", "C", "B"},
		base::math::Path{"E", "F", "D"},
	};

	base::List<base::math::Point> all_points = paths.AllPoints();
	base::Combination combination{all_points.Count(), 3};

	int count = 0;
	while (combination.MoveToNext())
	{
		base::math::Point point1 = all_points[combination[0]];
		base::math::Point point2 = all_points[combination[1]];
		base::math::Point point3 = all_points[combination[2]];

		if (paths.FindPaths(base::List<base::math::Point>{point1, point2}).Count() == 0)
		{
			continue;
		}

		if (paths.FindPaths(base::List<base::math::Point>{point1, point3}).Count() == 0)
		{
			continue;
		}

		if (paths.FindPaths(base::List<base::math::Point>{point2, point3}).Count() == 0)
		{
			continue;
		}

		if (paths.FindPaths(base::List<base::math::Point>{point1, point2, point3}).Count() > 0)
		{
			continue;
		}

		std::cout << point1 << ", "
				  << point2 << ", "
				  << point3
				  << std::endl;

		count++;
	}

	std::cout << "一共有 " << count << " 种情况。" << std::endl;
}
#endif
