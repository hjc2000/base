#pragma once

namespace base
{
	///
	/// @brief String 类的 Split 方法的选项。
	///
	///
	struct StringSplitOptions
	{
		///
		/// @brief 切割完之后是否对每个子字符串进行 Trim. 即去除头尾的空白字符。
		///
		/// @note 如果 Trim 之后变成空字符串，并且 remove_empty_substring
		/// 选项为 true，则该字符串将会被移除。
		///
		/// @note 默认值：false.
		///
		bool trim_each_substring = false;

		///
		/// @brief 是否移除切割出的空的子字符串。
		///
		/// @note 如果为 true，连续在一起的分隔符不会导致切割出一个空字符串。
		/// 例如逗号作分隔符时， "123,,456" 不会被切割成 3 个字符串，即不会被切割成
		/// 	@li "123"
		/// 	@li ""
		/// 	@li "456"
		/// 而是会被切割成
		/// 	@li "123"
		/// 	@li "456"
		/// 空字符串被丢弃。
		///
		/// @note 默认值：true.
		///
		bool remove_empty_substring = true;
	};

} // namespace base
