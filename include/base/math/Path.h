#pragma once
#include "base/container/iterator/IEnumerable.h"
#include "base/container/List.h"
#include "base/container/Set.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <string>

namespace base
{
	namespace math
	{
		using Point = std::string;

		/**
		 * @brief 路径。
		 *
		 */
		class Path :
			public base::ICanToString,
			public base::IEnumerable<base::math::Point const>
		{
		private:
			base::List<base::math::Point> _points;

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
			Path(base::List<base::math::Point> const &points);

			/**
			 * @brief 构造一条路径。
			 *
			 * @param points 这条路径上有哪些点。
			 */
			Path(std::initializer_list<base::math::Point> const &points);

			/**
			 * @brief 析构函数。
			 *
			 */
			virtual ~Path() = default;

		public:
			/**
			 * @brief 获取本路径中的点。
			 *
			 * @return base::List<base::math::Point> const&
			 */
			base::List<base::math::Point> const &Points() const;

			/**
			 * @brief 获取本路径的点集。
			 *
			 * @return base::Set<base::math::Point>
			 */
			base::Set<base::math::Point> PointSet() const;

			/**
			 * @brief 本路径中点的数量。
			 *
			 * @return int32_t
			 */
			int32_t PointsCount() const;

			/**
			 * @brief 添加一个点到路径末尾。
			 *
			 * @param point
			 * @return true 路径中没有该点，添加成功
			 * @return false 路径中已经有该点了，添加失败。
			 */
			bool AddPoint(base::math::Point const &point);

			/**
			 * @brief 移除点。
			 *
			 * @param point
			 * @return true 路径中有该点，移除成功。
			 * @return false 路径中没有该点，移除失败。
			 */
			bool RemovePoint(base::math::Point const &point);

			/**
			 * @brief 路径中是否含有该点。
			 *
			 * @param point
			 * @return true 含有该点。
			 * @return false 不含该点。
			 */
			bool ContainsPoint(base::math::Point const &point) const;

			/**
			 * @brief 检查本路径是否包含 points 中所有的点。
			 *
			 * @param points
			 * @return true
			 * @return false
			 */
			bool ContainsAllPoints(base::List<base::math::Point> const &points) const;

		public:
			/**
			 * @brief 获取本路径与另一个路径的交集点。
			 *
			 * @param another_path
			 * @return base::math::Path
			 */
			base::math::Path operator&(base::math::Path const &another_path) const;

			/**
			 * @brief 转化为字符串
			 *
			 * @return base::math::Point
			 */
			virtual std::string ToString() const override;

			/**
			 * @brief 获取非 const 迭代器
			 *
			 * @return std::shared_ptr<base::IEnumerator<ItemType>>
			 */
			virtual std::shared_ptr<base::IEnumerator<base::math::Point const>> GetEnumerator() override;
		};
	} // namespace math
} // namespace base
