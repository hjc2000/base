#pragma once
#include "base/container/IList.h"
#include "base/container/List.h"
#include "base/math/Path.h"
#include <initializer_list>

namespace base
{
	namespace math
	{
		class PathCollection :
			public base::IList<base::math::Path>
		{
		private:
			base::List<base::math::Path> _paths;

		public:
			PathCollection() = default;

			PathCollection(std::initializer_list<base::math::Path> const &paths);

		public:
			using base::IList<base::math::Path>::Add;

			/**
			 * @brief 向列表末尾添加一个元素。
			 *
			 * @param item
			 */
			virtual void Add(base::math::Path const &item) override;

			/**
			 * @brief 将元素插入列表指定位置。
			 *
			 * @param index
			 * @param item
			 */
			virtual void Insert(int32_t index, base::math::Path const &item) override;

			using base::IList<base::math::Path>::Remove;

			/**
			 * @brief 从列表移除指定元素。
			 *
			 * @note 如果列表中有重复元素，调用一次本方法只会移除一个。
			 *
			 * @param item
			 * @return true
			 * @return false
			 */
			virtual bool Remove(base::math::Path const &item) override;

			/**
			 * @brief 移除指定索引位置的元素。
			 *
			 * @param index
			 */
			virtual void RemoveAt(int32_t index) override;

			/**
			 * @brief 移除符合条件的数据。
			 *
			 * @param should_remove 用来指示特定的元素是否应该从容器中移除。
			 */
			virtual void RemoveIf(std::function<bool(base::math::Path const &item)> should_remove) override;

			/**
			 * @brief 查找指定元素的索引。
			 *
			 * @param item
			 * @return int32_t
			 */
			virtual int32_t IndexOf(base::math::Path const &item) const override;

			/**
			 * @brief 检查列表中是否含有该元素。
			 *
			 * @param item
			 * @return true
			 * @return false
			 */
			virtual bool Contains(base::math::Path const &item) const override;

			/**
			 * @brief 清空列表。
			 *
			 */
			virtual void Clear() override;

			/**
			 * @brief 列表中元素的数量。
			 *
			 * @return int32_t
			 */
			virtual int32_t Count() const override;

			/**
			 * @brief 获取指定索引位置的元素。
			 *
			 * @param index
			 * @return base::math::Path&
			 */
			virtual base::math::Path &operator[](int32_t index) override;

			/**
			 * @brief 获取指定索引位置的元素。
			 *
			 * @param index
			 * @return base::math::Path const&
			 */
			virtual base::math::Path const &operator[](int32_t index) const override;

		public:
			/**
			 * @brief 获取本路径集合中所有路径所经过的所有点的列表。
			 *
			 * @return base::List<base::math::Point>
			 */
			base::List<base::math::Point> AllPoints() const;

			/**
			 * @brief 找到一条路径经过 points 中所有的点。
			 *
			 * @param points
			 * @return base::List<base::math::Path>
			 */
			base::List<base::math::Path> FindPaths(base::List<base::math::Point> const &points) const;
		};
	} // namespace math
} // namespace base
