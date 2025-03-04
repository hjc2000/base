#pragma once
#include <base/container/List.h>
#include <initializer_list>
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

		/**
		 * @brief 构造一条线段。
		 *
		 * @param points 这条线段上有哪些点。
		 * @note 必须至少有 2 个点。
		 */
		LineSegmentPath(std::initializer_list<std::string> const &points);

	public:
		/**
		 * @brief 获取本路径中的点。
		 *
		 * @return base::List<std::string> const&
		 */
		base::List<std::string> const &Points() const;

		/**
		 * @brief 添加一个点到路径末尾。
		 *
		 * @param point
		 * @return true 路径中没有该点，添加成功
		 * @return false 路径中已经有该点了，添加失败。
		 */
		bool AddPoint(std::string const &point);

		/**
		 * @brief 移除点。
		 *
		 * @param point
		 * @return true 路径中有该点，移除成功。
		 * @return false 路径中没有该点，移除失败。
		 */
		bool RemovePoint(std::string const &point);

		/**
		 * @brief 路径中是否含有该点。
		 *
		 * @param point
		 * @return true 含有该点。
		 * @return false 不含该点。
		 */
		bool ContainsPoint(std::string const &point) const;
	};
} // namespace base
