#pragma once
#include <base/container/List.h>
#include <string>

namespace base
{
	/**
	 * @brief 线段路径。
	 *
	 */
	class LineSegmentPath
	{
	private:
		base::List<std::string> _points;

	public:
		/**
		 * @brief 构造一条线段。
		 *
		 * @param points 这条线段上有哪些点。
		 * @note 必须至少有 2 个点。
		 */
		LineSegmentPath(base::List<std::string> const &points);

	public:
		/**
		 * @brief 获取本路径中的点。
		 *
		 * @return base::List<std::string> const&
		 */
		base::List<std::string> const &Points() const;
	};
} // namespace base
