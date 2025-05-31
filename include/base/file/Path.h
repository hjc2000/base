#pragma once
#include "base/string/ICanToString.h"
#include "base/string/String.h"
#include <string>

namespace base
{
	class Path :
		public base::ICanToString
	{
	private:
		base::String _path;

		///
		/// @brief 更正路径为标准形式。
		///
		///
		void CorrectPath();

	public:
		/* #region 构造函数 */

		Path() = default;

		Path(base::String const &path);

		Path(std::string const &path);

		Path(char const *path);

		/* #endregion */

		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;

		///
		/// @brief 检查本路径是否是根路径。
		///
		/// @return true
		/// @return false
		///
		bool IsRootPath() const;

		///
		/// @brief 是绝对路径。
		///
		/// @return true
		/// @return false
		///
		bool IsAbsolutePath() const;

		///
		/// @brief 是 windows 风格的以盘符开头的路径。
		///
		/// @return true
		/// @return false
		///
		bool IsWindowsSytlePath() const;

		///
		/// @brief 将一个相对路径拼接到本路径的后面。
		///
		/// @param another
		/// @return base::Path
		///
		base::Path operator+(base::Path const &another) const;

		///
		/// @brief 将一个相对路径拼接到本路径的后面。
		///
		/// @param another
		/// @return base::Path&
		///
		base::Path &operator+=(base::Path const &another);

		///
		/// @brief 将本路径移除基础路径，留下后面的部分。这么做之后，本路径变成相对于 base_path
		/// 的相对路径。
		///
		/// @param base_path
		/// @return base::Path
		///
		base::Path RemoveBasePath(base::Path const &base_path) const;

		///
		/// @brief 获取本路径的父路径。
		///
		/// @return
		///
		base::Path ParentPath() const;
	};

#if HAS_THREAD

	namespace test
	{
		void test_path();
	} // namespace test

#endif // HAS_THREAD
} // namespace base
