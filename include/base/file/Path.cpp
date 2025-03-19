#include "Path.h"
#include "base/container/Range.h"
#include "base/string/character.h"
#include "base/string/define.h"
#include "base/string/String.h"
#include <stdexcept>

base::Path::Path(base::String const &path)
{
	_path = path;

	_path.Replace('\\', '/');

	while (_path.Contains("//"))
	{
		_path.Replace("//", "/");
	}

	// 去除相对路径的 ./
	if (_path.StartWith("./"))
	{
		_path = _path[base::Range{2, _path.Length()}];
	}

	// 去除路径结尾的斜杠
	if (_path.Length() > 1 && _path.EndWith('/'))
	{
		_path = _path[base::Range{0, _path.Length() - 1}];
	}

	// 如果是 windows 的类似 C: 这种路径，给它加上结尾的斜杠
	if (_path.Length() == 2 &&
		base::character::IsAlpha(_path[0]) &&
		_path[1] == ':')
	{
		if (!_path.EndWith('/'))
		{
			_path += '/';
		}
	}

	// 如果是 windows 路径，将盘符统一转为大写。
	if (_path.Length() >= 2 &&
		base::character::IsAlpha(_path[0]) &&
		_path[1] == ':')
	{
		_path[0] = base::character::ToUpper(_path[0]);
	}
}

std::string base::Path::ToString() const
{
	return _path.StdString();
}

bool base::Path::IsRootPath() const
{
	if (_path.Length() == 3 &&
		base::character::IsAlpha(_path[0]) &&
		_path[1] == ':' &&
		_path[2] == '/')
	{
		// 是 windows 的类似 C:/ 这种路径
		return true;
	}

	if (_path == '/')
	{
		return true;
	}

	return false;
}

bool base::Path::IsAbsolutePath() const
{
	if (_path.StartWith('/'))
	{
		return true;
	}

	// 是 windows 风格的绝对路径
	if (_path.Length() >= 2 &&
		base::character::IsAlpha(_path[0]) &&
		_path[1] == ':')
	{
		return true;
	}

	return false;
}

bool base::Path::IsWindowsDiskPath() const
{
	if (_path.Length() >= 2 &&
		base::character::IsAlpha(_path[0]) &&
		_path[1] == ':')
	{
		return true;
	}

	return false;
}

base::Path base::Path::operator+(base::Path const &another)
{
	base::Path ret{*this};
	ret += another;
	return ret;
}

base::Path &base::Path::operator+=(base::Path const &another)
{
	if (!IsAbsolutePath())
	{
		throw std::invalid_argument{CODE_POS_STR + "本路径必须是绝对路径才能拼接一个相对路径到本路径。"};
	}

	if (another.IsAbsolutePath())
	{
		throw std::invalid_argument{CODE_POS_STR + "要被拼接到本路径的路径必须是相对路径。"};
	}

	_path += another._path;
	return *this;
}

void base::Path::RemoveBasePath(base::Path const &base_path)
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
