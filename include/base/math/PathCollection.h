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
			virtual void Insert(int64_t index, base::math::Path const &item) override;

			/**
			 * @brief 移除指定索引位置的元素。
			 *
			 * @param index
			 */
			virtual void RemoveAt(int64_t index) override;

			/**
			 * @brief 移除符合条件的数据。
			 *
			 * @param should_remove 用来指示特定的元素是否应该从容器中移除。
			 */
			void RemoveIf(std::function<bool(base::math::Path const &item)> should_remove);

			/**
			 * @brief 清空列表。
			 *
			 */
			virtual void Clear() override;

			/**
			 * @brief 列表中元素的数量。
			 *
			 * @return int64_t
			 */
			virtual int64_t Count() const override;

			///
			/// @brief 获取指定索引位置的元素。
			///
			/// @param index
			///
			/// @return
			///
			virtual base::math::Path &Get(int64_t index) override
			{
				return _paths[index];
			}

			///
			/// @brief 获取指定索引位置的元素。
			///
			/// @param index
			///
			/// @return
			///
			virtual base::math::Path const &Get(int64_t index) const override
			{
				return _paths[index];
			}

			///
			/// @brief 设置指定位置的元素。
			///
			/// @param index
			/// @param value
			///
			virtual void Set(int64_t index, base::math::Path const &value) override
			{
				_paths[index] = value;
			}

		public:
			/**
			 * @brief 获取本路径集合中所有路径所经过的所有点的列表。
			 *
			 * @return
			 */
			base::List<base::math::Point> AllPoints() const;

			/**
			 * @brief 找到一条路径经过 points 中所有的点。
			 *
			 * @param points
			 *
			 * @return
			 */
			base::List<base::math::Path> FindPaths(base::List<base::math::Point> const &points) const;
		};

	} // namespace math
} // namespace base
