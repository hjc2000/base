#include "Path.h"
#include <cstdint>

base::math::Path::Path(base::List<Point> const &points)
{
	for (Point const &point : points)
	{
		AddPoint(point);
	}
}

base::math::Path::Path(std::initializer_list<Point> const &points)
{
	for (Point const &point : points)
	{
		AddPoint(point);
	}
}

base::List<base::math::Point> const &base::math::Path::Points() const
{
	return _points;
}

int32_t base::math::Path::PointsCount() const
{
	return _points.Count();
}

bool base::math::Path::AddPoint(Point const &point)
{
	if (_points.Contains(point))
	{
		return false;
	}

	_points.Add(point);
	return true;
}

bool base::math::Path::RemovePoint(Point const &point)
{
	return _points.Remove(point);
}

bool base::math::Path::ContainsPoint(Point const &point) const
{
	return _points.Contains(point);
}

base::math::Path base::math::Path::IntersectionPoints(base::math::Path const &another_path) const
{
	base::math::Path ret;
	for (Point const &point : _points)
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

std::string base::math::Path::ToString() const
{
	Point ret;
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
void base::math::test::test_path()
{
	base::math::Path path1{"A", "B", "C"};
	base::math::Path path2{"A", "B", "D"};
	base::math::Path path3{"A", "E", "F"};
	std::cout << (path1 & path2 & path3) << std::endl;
}
#endif
