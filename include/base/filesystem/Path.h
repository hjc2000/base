#pragma once
#include "base/container/List.h"
#include "base/container/Range.h"
#include "base/string/character.h"
#include "base/string/define.h"
#include "base/string/ICanToString.h"
#include "base/string/String.h"
#include <cstdint>
#include <stdexcept>
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
		void CorrectPath()
		{
			_path.Replace('\\', '/');

			while (_path.Contains("//"))
			{
				_path.Replace("//", "/");
			}

			// 去除开头的相对路径的 ./
			if (_path.StartWith("./"))
			{
				_path = _path[base::Range{2, _path.Length()}];
			}

			// 去除中间部分的冗余的 ./
			while (_path.Contains("/./"))
			{
				_path.Replace("/./", "/");
			}

			// 去除路径结尾的斜杠，除非路径只有一个 / ，即根路径。
			// 所以加了判断，_path.Length() > 1.
			if (_path.Length() > 1 && _path.EndWith('/'))
			{
				_path = _path[base::Range{0, _path.Length() - 1}];
			}

			// 如果是 windows 的类似 C: 这种路径，给它加上结尾的斜杠
			if (_path.Length() == 2 &&
				base::character::is_alpha(_path[0]) &&
				_path[1] == ':')
			{
				if (!_path.EndWith('/'))
				{
					_path += '/';
				}
			}

			// 如果是 windows 路径，将盘符统一转为大写。
			if (_path.Length() >= 2 &&
				base::character::is_alpha(_path[0]) &&
				_path[1] == ':')
			{
				_path[0] = base::character::to_upper(_path[0]);
			}
		}

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
		bool IsRootPath() const
		{
			if (_path.Length() == 3 &&
				base::character::is_alpha(_path[0]) &&
				_path[1] == ':' &&
				_path[2] == '/')
			{
				// 是 windows 的类似 C:/ 这种路径
				return true;
			}

			if (_path == "/")
			{
				return true;
			}

			return false;
		}

		///
		/// @brief 是绝对路径。
		///
		/// @return
		///
		bool IsAbsolutePath() const
		{
			if (_path.StartWith('/'))
			{
				return true;
			}

			// 是 windows 风格的绝对路径
			if (_path.Length() >= 2 &&
				base::character::is_alpha(_path[0]) &&
				_path[1] == ':')
			{
				return true;
			}

			return false;
		}

		///
		/// @brief 是 windows 风格的以盘符开头的路径。
		///
		/// @return
		///
		bool IsWindowsSytlePath() const
		{
			if (_path.Length() >= 2 &&
				base::character::is_alpha(_path[0]) &&
				_path[1] == ':')
			{
				return true;
			}

			return false;
		}

		///
		/// @brief 将一个相对路径拼接到本路径的后面。
		///
		/// @param another
		/// @return
		///
		base::Path operator+(base::Path const &another) const
		{
			if (another.IsAbsolutePath())
			{
				throw std::invalid_argument{CODE_POS_STR + "要被拼接到本路径的路径必须是相对路径。"};
			}

			if (_path == "")
			{
				return base::Path{another._path};
			}

			return base::Path{_path + '/' + another._path};
		}

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
		void RemoveBasePath(base::Path const &base_path)
		{
			base::String base_path_str = base_path.ToString();
			if (!base_path_str.EndWith('/'))
			{
				base_path_str += '/';
			}

			if (!_path.StartWith(base_path_str))
			{
				throw std::invalid_argument{
					CODE_POS_STR +
					base_path.ToString() +
					" 不是本路径 " +
					ToString() +
					" 的相对路径。"};
			}

			_path = _path[base::Range{base_path_str.Length(), _path.Length()}];
		}

		///
		/// @brief 获取本路径的父路径。
		///
		/// @return
		///
		base::Path ParentPath() const
		{
			if (IsRootPath())
			{
				throw std::runtime_error{CODE_POS_STR + "根路径没有父路径。"};
			}

			int32_t index = _path.LastIndexOf('/');

			if (index < 0)
			{
				return "";
			}

			return base::Path{_path[base::Range{0, index}]};
		}

		///
		/// @brief 获取路径中最后一级的名称。
		///
		/// @note 即最后一个斜杠后面的名称。这可能是个目录名，也可能是个文件名。
		///
		/// @return
		///
		base::Path LastName() const
		{
			if (_path.Length() == 0)
			{
				std::string message = CODE_POS_STR;
				message += "本路径为空字符串，表示当前路径，无法获取最后一级路径的名称。";
				throw std::runtime_error{message};
			}

			int32_t index = _path.LastIndexOf('/');
			if (index < 0)
			{
				// 不包含斜杠，说明是相对路径，并且只有一级，则直接返回自己，
				// 自己已经是最后一级的名称了。
				return base::Path{*this};
			}

			return base::Path{_path[base::Range{index + 1, _path.Length()}]};
		}

		///
		/// @brief 更改最后一级名称。
		///
		/// @param value
		///
		void SetLastName(base::String const &value)
		{
			base::Path base_path{};

			int32_t index = _path.LastIndexOf('/');
			if (index > 0)
			{
				base_path = base::Path{_path[base::Range{0, index}]};
			}

			*this = base_path + value;
		}

		///
		/// @brief 没有扩展名的名称。
		///
		/// @return
		///
		base::String NameWithoutExtension() const
		{
			base::Path last_name = LastName();
			int32_t index = last_name._path.LastIndexOf('.');

			if (index < 0)
			{
				return last_name._path;
			}

			if (index == last_name._path.Length() - 1)
			{
				// 路径以点结尾，没有扩展名
				return last_name._path;
			}

			return last_name._path[base::Range{0, index}];
		}

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
		base::String ExtensionName() const
		{
			base::Path last_name = LastName();
			int32_t index = last_name._path.LastIndexOf('.');

			if (index < 0)
			{
				return base::String{};
			}

			if (index == last_name._path.Length() - 1)
			{
				// 路径以点结尾，没有扩展名
				return base::String{};
			}

			return last_name._path[base::Range{index + 1, last_name._path.Length()}];
		}

		bool operator==(base::Path const &other) const
		{
			return _path == other._path;
		}
	};

	///
	/// @brief 简单的自然排序。
	///
	/// @param paths
	///
	inline void simple_natural_sort(base::List<base::Path> &paths)
	{
		base::List<std::string> path_strings{};

		for (base::Path const &path : paths)
		{
			path_strings.Add(path.ToString());
		}

		base::simple_natural_sort(path_strings);
		paths.Clear();

		for (std::string const &path_string : path_strings)
		{
			paths.Add(base::Path{path_string});
		}
	}

} // namespace base
