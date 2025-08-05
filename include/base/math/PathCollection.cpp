#include "PathCollection.h"
#include "Path.h"

base::math::PathCollection::PathCollection(std::initializer_list<base::math::Path> const &paths)
{
	_paths.Add(paths);
}

void base::math::PathCollection::Add(base::math::Path const &item)
{
	_paths.Add(item);
}

void base::math::PathCollection::Insert(int64_t index, base::math::Path const &item)
{
	_paths.Insert(index, item);
}

void base::math::PathCollection::RemoveAt(int64_t index)
{
	_paths.RemoveAt(index);
}

void base::math::PathCollection::RemoveIf(std::function<bool(base::math::Path const &item)> should_remove)
{
	_paths.RemoveIf(should_remove);
}

void base::math::PathCollection::Clear()
{
	_paths.Clear();
}

int64_t base::math::PathCollection::Count() const
{
	return _paths.Count();
}

base::List<base::math::Point> base::math::PathCollection::AllPoints() const
{
	base::Set<base::math::Point> all_points_set;
	for (base::math::Path const &path : _paths)
	{
		all_points_set.Add(path.PointSet());
	}

	base::List<base::math::Point> ret;
	for (base::math::Point const &point : all_points_set)
	{
		ret.Add(point);
	}

	return ret;
}

base::List<base::math::Path> base::math::PathCollection::FindPaths(base::List<base::math::Point> const &points) const
{
	base::List<base::math::Path> ret;
	for (auto &path : _paths)
	{
		if (path.ContainsAllPoints(points))
		{
			ret.Add(path);
		}
	}

	return ret;
}
