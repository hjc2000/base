#pragma once
#include "base/string/String.h"

namespace base
{
	///
	/// @brief 键值对字符串。
	///
	///
	class KeyValueString
	{
	private:
		base::String _key;
		base::String _value;

		void CheckKeyValue() const;

	public:
		///
		/// @brief 通过键值对字符串构造。
		///
		/// @param key_value_string 形如 "key = value" 的字符串。
		///
		KeyValueString(base::String const key_value_string);

		///
		/// @brief 通过键字符串和值字符串构造。
		///
		/// @param key
		/// @param value
		///
		KeyValueString(base::String const &key, base::String const &value);

		base::String &Key()
		{
			return _key;
		}

		base::String const &Key() const
		{
			return _key;
		}

		base::String &Value()
		{
			return _value;
		}

		base::String const &Value() const
		{
			return _value;
		}

		base::String KeyValue() const
		{
			return _key + _value;
		}
	};
} // namespace base
