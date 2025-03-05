#include "CountTriangle.h"
#include <base/math/Combination.h>
#include <iostream>

#if HAS_THREAD

void base::math::CountTriangle(base::math::PathCollection const &paths)
{
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
