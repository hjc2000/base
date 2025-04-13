#include "KeyScanner.h" // IWYU pragma: keep
#include "base/task/delay.h"
#include <cstddef>

void base::key::KeyScanner::ScanKeysNoDelay(boost::dynamic_bitset<> &out)
{
	for (size_t i = 0; i < _keys.size(); i++)
	{
		out[i] = _keys[i].KeyIsDown();
	}
}

base::key::KeyScanner::KeyScanner(std::initializer_list<base::key::Key> keys)
{
	for (base::key::Key const &key : keys)
	{
		_keys.push_back(key);
	}
}

void base::key::KeyScanner::ScanKeys()
{
	_last_scan_result = _current_scan_result;
	ScanKeysNoDelay(_no_delay_scan_result1);
	base::task::Delay(std::chrono::milliseconds{10});
	ScanKeysNoDelay(_no_delay_scan_result2);
	_current_scan_result = _no_delay_scan_result1 & _no_delay_scan_result2;
}

bool base::key::KeyScanner::HasKeyDownEvent(int key_index) const
{
	return _current_scan_result[key_index] && (!_last_scan_result[key_index]);
}

bool base::key::KeyScanner::HasKeyUpEvent(int key_index) const
{
	return (!_current_scan_result[key_index]) && _last_scan_result[key_index];
}

bool base::key::KeyScanner::HasKeyPressedEvent(int key_index) const
{
	return _current_scan_result[key_index];
}
