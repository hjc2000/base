#include "Path.h"
#include "base/container/Range.h"
#include "base/string/character.h"
#include "base/string/define.h"
#include "base/string/String.h"
#include <stdexcept>

void base::Path::CorrectPath()
{
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

	while (_path.Contains("/./"))
	{
		_path.Replace("/./", "/");
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

base::Path::Path(base::String const &path)
{
	_path = path;
	_path.Trim();
	CorrectPath();
}

base::Path::Path(std::string const &path)
	: base::Path(base::String{path})
{
}

base::Path::Path(char const *path)
	: base::Path(base::String{path})
{
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

base::Path &base::Path::operator+=(base::Path const &another)
{
	base::Path sum = *this + another;
	*this = sum;
	return *this;
}

base::Path base::Path::RemoveBasePath(base::Path const &base_path) const
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

	base::String str = _path[base::Range{base_path_str.Length(), _path.Length()}];
	return base::Path{str};
}

#if HAS_THREAD

void base::test::test_path()
{
	base::Path path{"C:/Users/huang/dev/cpp-lib-build-scripts/msys/.libs/base/bin/"};
	std::cout << path << std::endl;
	std::cout << "IsRootPath: " << path.IsRootPath() << std::endl;
	std::cout << "IsAbsolutePath: " << path.IsAbsolutePath() << std::endl;
	std::cout << "IsWindowsDiskPath: " << path.IsWindowsDiskPath() << std::endl;

	base::Path path1 = path;
	path1.RemoveBasePath("C:/Users/huang/dev/cpp-lib-build-scripts/");
	std::cout << path1 << std::endl;
	std::cout << "IsRootPath: " << path1.IsRootPath() << std::endl;
	std::cout << "IsAbsolutePath: " << path1.IsAbsolutePath() << std::endl;
	std::cout << "IsWindowsDiskPath: " << path1.IsWindowsDiskPath() << std::endl;

	std::cout << "拼接结果：" << (path + path1) << std::endl;
}

#endif // HAS_THREAD
