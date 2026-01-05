#pragma once
#include "base/math/Combination.h"
#include "base/math/PathCollection.h"
#include <iostream>

namespace base::usage
{
	///
	/// @brief 数出路径集 paths 中的路径围成的三角形个数。
	///
	/// @param paths 路径集合。本函数认为这里面的路径都是线段。
	///
	inline void CountTriangle(base::math::PathCollection const &paths)
	{
		base::List<base::math::Point> all_points = paths.AllPoints();
		base::Combination combination{all_points.Count(), 3};

		int64_t count = 0;

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

	///
	/// @brief 测试 CountTriangle.
	///
	inline void CountTriangle()
	{
		base::math::PathCollection paths{
			base::math::Path{"A", "B", "D", "G"},
			base::math::Path{"C", "D", "H"},
			base::math::Path{"F", "G", "H"},
			base::math::Path{"A", "C", "F"},
			base::math::Path{"E", "C", "B"},
			base::math::Path{"E", "F", "D"},
		};

		CountTriangle(paths);
	}

} // namespace base::usage
