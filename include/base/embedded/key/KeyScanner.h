#pragma once
#include "boost/dynamic_bitset/dynamic_bitset.hpp"
#include "Key.h"
#include <initializer_list>
#include <vector>

namespace base
{
	namespace key
	{
		///
		/// @brief 按键扫描器。
		///
		///
		class KeyScanner
		{
		private:
			std::vector<base::key::Key> _keys{};
			boost::dynamic_bitset<> _last_scan_result{};
			boost::dynamic_bitset<> _current_scan_result{};
			boost::dynamic_bitset<> _no_delay_scan_result1{};
			boost::dynamic_bitset<> _no_delay_scan_result2{};

			boost::dynamic_bitset<> _key_down_events{};
			boost::dynamic_bitset<> _key_up_events{};

			void ScanKeysNoDelay(boost::dynamic_bitset<> &out);

		public:
			///
			/// @brief 构造按键扫描器。
			///
			/// @param keys 要添加进来被扫描器扫描的按键。
			///
			KeyScanner(std::initializer_list<base::key::Key> const &keys);

			///
			/// @brief 获取被本扫描器扫描的按键列表。
			///
			/// @return std::vector<base::key::Key> const&
			///
			std::vector<base::key::Key> const &Keys() const
			{
				return _keys;
			}

			///
			/// @brief 扫描按键。扫描后事件会得到更新。
			///
			///
			void ScanKeys();

			///
			/// @brief 检查某个按键是否有被按下事件。
			///
			/// @param key_index 构造本扫描器时在构造函数初始化列表中的索引。
			/// @return true
			/// @return false
			///
			bool HasKeyDownEvent(int key_index) const;

			///
			/// @brief 检查某个按键是否有被抬起事件。
			///
			/// @param key_index 构造本扫描器时在构造函数初始化列表中的索引。
			/// @return true
			/// @return false
			///
			bool HasKeyUpEvent(int key_index) const;

			///
			/// @brief 检查某个按键是否处于被按下的状态。
			///
			/// @param key_index 构造本扫描器时在构造函数初始化列表中的索引。
			/// @return true
			/// @return false
			///
			bool HasKeyPressedEvent(int key_index) const;
		};

	} // namespace key
} // namespace base
