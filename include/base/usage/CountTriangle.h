#pragma once
#if HAS_THREAD
	#include <base/math/PathCollection.h>

namespace base
{
	namespace usage
	{
		///
		/// @brief 数出路径集 paths 中的路径围成的三角形个数。
		///
		/// @param paths 路径集合。本函数认为这里面的路径都是线段。
		///
		void CountTriangle(base::math::PathCollection const &paths);

		///
		/// @brief 测试 CountTriangle.
		///
		///
		void CountTriangle();
	} // namespace usage
} // namespace base
#endif
