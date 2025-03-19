#include "Path.h"
#include "base/container/Range.h"

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
	if (_path.EndWith('/'))
	{
		_path = _path[base::Range{0, _path.Length() - 1}];
	}
}

std::string base::Path::ToString() const
{
	return _path.StdString();
}
