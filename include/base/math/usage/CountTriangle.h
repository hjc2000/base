#pragma once
#if HAS_THREAD
	#include <base/math/PathCollection.h>

namespace base
{
	namespace math
	{
		/**
		 * @brief 数出路径集 paths 中的路径围成的三角形个数。
		 *
		 * @param paths 路径集合。本函数认为这里面的路径都是线段。
		 */
		void CountTriangle(base::math::PathCollection const &paths);

		/**
		 * @brief 测试 CountTriangle.
		 *
		 */
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
	} // namespace math
} // namespace base
#endif
