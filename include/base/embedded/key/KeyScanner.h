#pragma once
#include "base/task/delay.h"
#include "boost/dynamic_bitset/dynamic_bitset.hpp"
#include "Key.h"
#include <cstddef>
#include <initializer_list>
#include <vector>

namespace base::key
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

		void ScanKeysNoDelay(boost::dynamic_bitset<> &out)
		{
			for (size_t i = 0; i < _keys.size(); i++)
			{
				out[i] = _keys[i].KeyIsDown();
			}
		}

	public:
		///
		/// @brief 构造按键扫描器。
		///
		/// @param keys 要添加进来被扫描器扫描的按键。
		///
		KeyScanner(std::initializer_list<base::key::Key> const &keys)
		{
			_last_scan_result = boost::dynamic_bitset<>{keys.size()};
			_current_scan_result = boost::dynamic_bitset<>{keys.size()};
			_no_delay_scan_result1 = boost::dynamic_bitset<>{keys.size()};
			_no_delay_scan_result2 = boost::dynamic_bitset<>{keys.size()};
			_key_down_events = boost::dynamic_bitset<>{keys.size()};
			_key_up_events = boost::dynamic_bitset<>{keys.size()};

			for (base::key::Key const &key : keys)
			{
				_keys.push_back(key);
			}
		}

		///
		/// @brief 获取被本扫描器扫描的按键列表。
		///
		/// @return
		///
		std::vector<base::key::Key> const &Keys() const
		{
			return _keys;
		}

		///
		/// @brief 扫描按键。扫描后事件会得到更新。
		///
		void ScanKeys()
		{
			_last_scan_result = _current_scan_result;
			ScanKeysNoDelay(_no_delay_scan_result1);
			base::task::Delay(std::chrono::milliseconds{10});
			ScanKeysNoDelay(_no_delay_scan_result2);
			_current_scan_result = _no_delay_scan_result1 & _no_delay_scan_result2;

			_key_down_events = _current_scan_result & (~_last_scan_result);
			_key_up_events = (~_current_scan_result) & _last_scan_result;
		}

		///
		/// @brief 检查某个按键是否有被按下事件。
		///
		/// @param key_index 构造本扫描器时在构造函数初始化列表中的索引。
		///
		/// @return
		///
		bool HasKeyDownEvent(int key_index) const
		{
			return _key_down_events[key_index];
		}

		///
		/// @brief 检查某个按键是否有被抬起事件。
		///
		/// @param key_index 构造本扫描器时在构造函数初始化列表中的索引。
		///
		/// @return
		///
		bool HasKeyUpEvent(int key_index) const
		{
			return _key_up_events[key_index];
		}

		///
		/// @brief 检查某个按键是否处于被按下的状态。
		///
		/// @param key_index 构造本扫描器时在构造函数初始化列表中的索引。
		///
		/// @return
		///
		bool HasKeyPressedEvent(int key_index) const
		{
			return _current_scan_result[key_index];
		}
	};

} // namespace base::key
