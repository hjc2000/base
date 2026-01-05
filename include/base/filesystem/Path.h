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

		Path(base::String const &path)
		{
			_path = path;
			_path.Trim();
			CorrectPath();
		}

		Path(std::string const &path)
			: base::Path(base::String{path})
		{
		}

		Path(char const *path)
			: base::Path(base::String{path})
		{
		}

		/* #endregion */

		///
		/// @brief 转化为字符串。
		///
		/// @return
		///
		virtual std::string ToString() const override
		{
			return _path.StdString();
		}

		///
		/// @brief 检查本路径是否是根路径。
		///
		/// @return
		///
		bool IsRootPath() const;

		///
		/// @brief 是绝对路径。
		///
		/// @return
		///
		bool IsAbsolutePath() const;

		///
		/// @brief 是 windows 风格的以盘符开头的路径。
		///
		/// @return
		///
		bool IsWindowsSytlePath() const;

		///
		/// @brief 将一个相对路径拼接到本路径的后面。
		///
		/// @param another
		/// @return
		///
		base::Path operator+(base::Path const &another) const;

		///
		/// @brief 将一个相对路径拼接到本路径的后面。
		///
		/// @param another
		/// @return
		///
		base::Path &operator+=(base::Path const &another)
		{
			base::Path sum = *this + another;
			*this = sum;
			return *this;
		}

		///
		/// @brief 将本路径移除基础路径，留下后面的部分。这么做之后，本路径变成相对于 base_path
		/// 的相对路径。
		///
		/// @param base_path
		///
		void RemoveBasePath(base::Path const &base_path);

		///
		/// @brief 获取本路径的父路径。
		///
		/// @return
		///
		base::Path ParentPath() const;

		///
		/// @brief 获取路径中最后一级的名称。
		///
		/// @note 即最后一个斜杠后面的名称。这可能是个目录名，也可能是个文件名。
		///
		/// @return
		///
		base::Path LastName() const;

		///
		/// @brief 更改最后一级名称。
		///
		/// @param value
		///
		void SetLastName(base::String const &value);

		///
		/// @brief 获取文件的扩展名。
		///
		/// @note 解析字符串，获取 LastName 中的最后一个点后面的部分。
		/// 如果没有扩展名，则返回空字符串。
		///
		/// @note 不包括 “点” 本身。
		///
		/// @return
		///
		base::String ExtensionName() const;

		bool operator==(base::Path const &other) const
		{
			return _path == other._path;
		}
	};

} // namespace base
