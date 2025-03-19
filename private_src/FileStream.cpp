#include "FileStream.h" // IWYU pragma: keep

#if HAS_THREAD
	#include <base/file/filesystem.h>

/* #region 构造，析构 */

base::FileStream::FileStream(std::string path)
{
	_path = path;
}

base::FileStream::~FileStream()
{
	Close();
}

/* #endregion */

/* #region 工厂函数 */

std::shared_ptr<base::FileStream> base::FileStream::OpenOrCreate(std::string path)
{
	try
	{
		if (!base::filesystem::exists(path))
		{
			return CreateNewAnyway(path);
		}

		// 执行到这里说明 path 存在。
		if (base::filesystem::is_directory(path))
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

std::shared_ptr<base::FileStream> base::FileStream::CreateNewAnyway(std::string path)
{
	if (base::filesystem::exists(path))
	{
		// 如果存在，不管是文件还是目录，统统删除。
		base::filesystem::remove(path);
	}

	std::shared_ptr<FileStream> fs{new FileStream{path}};

	auto flags = std::ios_base::out |
				 std::ios_base::in |
				 std::ios_base::trunc |
				 std::ios_base::binary;

	fs->_fs = std::shared_ptr<std::fstream>{new std::fstream{
		path,
		flags,
	}};

	if (fs->_fs->fail())
	{
		std::string message = CODE_POS_STR + std::format("创建 {} 失败。", path);
		throw std::runtime_error{message};
	}

	fs->_can_read = true;
	fs->_can_write = true;
	fs->_can_seek = true;
	return fs;
}

std::shared_ptr<base::FileStream> base::FileStream::OpenExisting(std::string path)
{
	if (!base::filesystem::exists(path))
	{
		throw std::runtime_error{CODE_POS_STR + std::format("文件 {} 不存在。", path)};
	}

	if (base::filesystem::is_directory(path))
	{
		throw std::runtime_error{CODE_POS_STR + std::format("{} 不是一个文件，而是一个目录", path)};
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
		path,
		flags,
	}};

	if (fs->_fs->fail())
	{
		std::string message = CODE_POS_STR + std::format("打开 {} 失败。", path);
		throw std::runtime_error{message};
	}

	fs->_can_read = true;
	fs->_can_write = true;
	fs->_can_seek = true;
	return fs;
}

std::shared_ptr<base::FileStream> base::FileStream::OpenReadOnly(std::string path)
{
	if (!base::filesystem::exists(path))
	{
		std::string message = CODE_POS_STR + std::format("文件 {} 不存在。", path);
		throw std::runtime_error{message};
	}

	if (base::filesystem::is_directory(path))
	{
		std::string message = CODE_POS_STR + std::format("{} 不是一个文件，而是一个目录", path);
		throw std::runtime_error{message};
	}

	if (!base::filesystem::IsReadable(path))
	{
		throw std::runtime_error{CODE_POS_STR + "文件不可读。"};
	}

	std::shared_ptr<FileStream> fs{new FileStream{path}};

	auto flags = std::ios_base::in | std::ios_base::binary;

	fs->_fs = std::shared_ptr<std::fstream>{new std::fstream{
		path,
		flags,
	}};

	if (fs->_fs->fail())
	{
		std::string message = CODE_POS_STR + std::format("以只读方式打开 {} 失败。", path);
		throw std::runtime_error{message};
	}

	fs->_can_read = true;
	fs->_can_write = false;
	fs->_can_seek = true;
	return fs;
}

/* #endregion */

/* #region 流属性 */

bool base::FileStream::CanRead() const
{
	return _can_read;
}

bool base::FileStream::CanWrite() const
{
	return _can_write;
}

bool base::FileStream::CanSeek() const
{
	return _can_seek;
}

int64_t base::FileStream::Length() const
{
	// 记录当前位置
	int64_t current_pos = _fs->tellg();

	// seek 到文件末尾
	_fs->seekg(0, _fs->end);

	// 记录文件末尾的位置（最后一个字节之后一个字节，所以 end_pos 等于文件长度）
	int64_t end_pos = _fs->tellg();

	// seek 回原来的位置
	_fs->seekg(current_pos);

	return end_pos;
}

void base::FileStream::SetLength(int64_t value)
{
	// 防止 Position 属性超出边界
	int64_t current_pos = Position();
	SetPosition(std::min(value, current_pos));

	// 重设大小
	std::filesystem::resize_file(_path.c_str(), value);
	std::cout << "更改大小后文件大小=" << Length() << std::endl;
}

int64_t base::FileStream::Position() const
{
	return _fs->tellg();
}

void base::FileStream::SetPosition(int64_t value)
{
	/* 必须先清除标志。因为如果不清除，上次读写如果触发了 eof 了，即使在这里 seek 到非尾部
	 * 下次读写流时仍会因为 eof 已经被设置了而无法读写。
	 */
	_fs->clear();
	_fs->seekg(value);
	_fs->seekp(value);
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
