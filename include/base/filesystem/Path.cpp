#include "Path.h"
#include "base/container/Range.h"
#include "base/string/character.h"
#include "base/string/define.h"
#include "base/string/String.h"
#include <cstdint>
#include <stdexcept>
#include <string>

void base::Path::CorrectPath()
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

bool base::Path::IsRootPath() const
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

bool base::Path::IsAbsolutePath() const
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

bool base::Path::IsWindowsSytlePath() const
{
	if (_path.Length() >= 2 &&
		base::character::is_alpha(_path[0]) &&
		_path[1] == ':')
	{
		return true;
	}

	return false;
}

base::Path base::Path::operator+(base::Path const &another) const
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

base::Path base::Path::ParentPath() const
{
	if (IsRootPath())
	{
		throw std::runtime_error{CODE_POS_STR + "根路径没有父路径。"};
	}

	int32_t index = _path.LastIndexOf('/');
	if (index < 0)
	{
		throw std::runtime_error{CODE_POS_STR + "没有斜杠了，已经无法提取出父路径名了。"};
	}

	return base::Path{_path[base::Range{0, index}]};
}

base::Path base::Path::LastName() const
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

void base::Path::SetLastName(base::String const &value)
{
	base::Path base_path{};

	int32_t index = _path.LastIndexOf('/');
	if (index > 0)
	{
		base_path = base::Path{_path[base::Range{0, index}]};
	}

	*this = base_path + value;
}

base::String base::Path::ExtensionName() const
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
