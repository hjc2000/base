#pragma once
#include "boost/dynamic_bitset/dynamic_bitset.hpp"
#include "Key.h"
#include <initializer_list>
#include <vector>

namespace base
{
	namespace key
	{
		class KeyScanner
		{
		private:
			std::vector<base::key::Key> _keys;
			boost::dynamic_bitset<> _last_scan_result;
			boost::dynamic_bitset<> _current_scan_result;
			boost::dynamic_bitset<> _no_delay_scan_result1;
			boost::dynamic_bitset<> _no_delay_scan_result2;

			void ScanKeysNoDelay(boost::dynamic_bitset<> &out);

		public:
			KeyScanner(std::initializer_list<base::key::Key> keys);

			std::vector<base::key::Key> const &Keys() const
			{
				return _keys;
			}

			void ScanKeys();

			bool HasKeyDownEvent(int key_index) const;

			bool HasKeyUpEvent(int key_index) const;

			bool HasKeyPressedEvent(int key_index) const;
		};
	} // namespace key
} // namespace base
