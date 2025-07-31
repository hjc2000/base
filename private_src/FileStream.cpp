#include "FileStream.h"

#if HAS_THREAD

/* #region 构造，析构 */

base::FileStream::FileStream(base::Path const &path)
{
	_path = path;
}

base::FileStream::~FileStream()
{
	Close();
}

/* #endregion */

/* #region 工厂函数 */

std::shared_ptr<base::FileStream> base::FileStream::OpenOrCreate(base::Path const &path)
{
	try
	{
		if (!base::filesystem::Exists(path))
		{
			return CreateNewAnyway(path);
		}

		// 执行到这里说明 path 存在。
		if (base::filesystem::IsDirectory(path))
		{
			// 是一个目录，直接创建新文件。
			return CreateNewAnyway(path);
		}

		// 存在，且不是目录，直接打开。
		return OpenExisting(path);
	}
	catch (std::exception const &e)
	{
		std::string message = CODE_POS_STR + e.what();
		throw std::runtime_error{message};
	}
}

std::shared_ptr<base::FileStream> base::FileStream::CreateNewAnyway(base::Path const &path)
{
	if (base::filesystem::Exists(path))
	{
		// 如果存在，不管是文件还是目录，统统删除。
		base::filesystem::Remove(path);
	}

	std::shared_ptr<FileStream> fs{new FileStream{path}};

	auto flags = std::ios_base::out |
				 std::ios_base::in |
				 std::ios_base::trunc |
				 std::ios_base::binary;

	fs->_fs = std::shared_ptr<std::fstream>{new std::fstream{
		path.ToString(),
		flags,
	}};

	if (fs->_fs->fail())
	{
		std::string message = CODE_POS_STR + std::format("创建 {} 失败。", path.ToString());
		throw std::runtime_error{message};
	}

	fs->_can_read = true;
	fs->_can_write = true;
	fs->_can_seek = true;
	return fs;
}

std::shared_ptr<base::FileStream> base::FileStream::OpenExisting(base::Path const &path)
{
	if (!base::filesystem::Exists(path))
	{
		throw std::runtime_error{CODE_POS_STR + std::format("文件 {} 不存在。", path.ToString())};
	}

	if (base::filesystem::IsDirectory(path))
	{
		throw std::runtime_error{CODE_POS_STR + std::format("{} 不是一个文件，而是一个目录", path.ToString())};
	}

	if (!base::filesystem::IsReadable(path))
	{
		throw std::runtime_error{CODE_POS_STR + "文件不可读。"};
	}

	if (!base::filesystem::IsWriteable(path))
	{
		throw std::runtime_error{CODE_POS_STR + "文件不可写。"};
	}

	std::shared_ptr<FileStream> fs{new FileStream{path}};

	auto flags = std::ios_base::in |
				 std::ios_base::out |
				 std::ios_base::binary;

	fs->_fs = std::shared_ptr<std::fstream>{new std::fstream{
		path.ToString(),
		flags,
	}};

	if (fs->_fs->fail())
	{
		std::string message = CODE_POS_STR + std::format("打开 {} 失败。", path.ToString());
		throw std::runtime_error{message};
	}

	fs->_can_read = true;
	fs->_can_write = true;
	fs->_can_seek = true;
	return fs;
}

std::shared_ptr<base::FileStream> base::FileStream::OpenReadOnly(base::Path const &path)
{
	if (!base::filesystem::Exists(path))
	{
		std::string message = CODE_POS_STR + std::format("文件 {} 不存在。", path.ToString());
		throw std::runtime_error{message};
	}

	if (base::filesystem::IsDirectory(path))
	{
		std::string message = CODE_POS_STR + std::format("{} 不是一个文件，而是一个目录", path.ToString());
		throw std::runtime_error{message};
	}

	if (!base::filesystem::IsReadable(path))
	{
		throw std::runtime_error{CODE_POS_STR + "文件不可读。"};
	}

	std::shared_ptr<FileStream> fs{new FileStream{path}};

	auto flags = std::ios_base::in | std::ios_base::binary;

	fs->_fs = std::shared_ptr<std::fstream>{new std::fstream{
		path.ToString(),
		flags,
	}};

	if (fs->_fs->fail())
	{
		std::string message = CODE_POS_STR + std::format("以只读方式打开 {} 失败。", path.ToString());
		throw std::runtime_error{message};
	}

	fs->_can_read = true;
	fs->_can_write = false;
	fs->_can_seek = true;
	return fs;
}

/* #endregion */

/* #region 流属性 */

void base::FileStream::SetLength(int64_t value)
{
	// 防止 Position 属性超出边界
	int64_t current_pos = Position();
	SetPosition(std::min(value, current_pos));

	// 重设大小
	std::filesystem::resize_file(_path.ToString().c_str(), value);
	std::cout << "更改大小后文件大小=" << Length() << std::endl;
}

/* #endregion */

/* #region 读写冲关 */

int32_t base::FileStream::Read(base::Span const &span)
{
	_fs->read(reinterpret_cast<char *>(span.Buffer()), span.Size());
	int32_t have_read = _fs->gcount();
	SetPosition(_fs->tellg());
	return have_read;
}

void base::FileStream::Write(base::ReadOnlySpan const &span)
{
	_fs->write(reinterpret_cast<char const *>(span.Buffer()), span.Size());
	SetPosition(_fs->tellp());
}

void base::FileStream::Flush()
{
	_fs->flush();
}

void base::FileStream::Close()
{
	_fs->close();
}

/* #endregion */

#endif // HAS_THREAD
