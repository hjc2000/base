#pragma once
#include <base/container/List.h>
#include <initializer_list>
#include <string>

namespace base
{
	namespace math
	{
		/**
		 * @brief 路径。
		 *
		 */
		class Path
		{
		private:
			base::List<std::string> _points;

		public:
			/**
			 * @brief 构造一条路径。
			 *
			 */
			Path() = default;

			/**
			 * @brief 构造一条路径。
			 *
			 * @param points 这条路径上有哪些点。
			 */
			Path(base::List<std::string> const &points);

			/**
			 * @brief 构造一条路径。
			 *
			 * @param points 这条路径上有哪些点。
			 */
			Path(std::initializer_list<std::string> const &points);

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

		public:
			/**
			 * @brief 获取本路径与另一个路径的交集点。
			 *
			 * @param another_path
			 * @return base::List<std::string>
			 */
			base::math::Path IntersectionPoints(base::math::Path const &another_path) const;

			/**
			 * @brief 获取本路径与另一个路径的交集点。
			 *
			 * @param another_path
			 * @return base::math::Path
			 */
			base::math::Path operator&(base::math::Path const &another_path) const;
		};
	} // namespace math
} // namespace base
