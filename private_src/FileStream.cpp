#include "FileStream.h"

#if HAS_THREAD

	#include <filesystem>
	#include <format>
	#include <iostream>

std::shared_ptr<base::FileStream> base::FileStream::CreateNewAnyway(std::string path)
{
	std::shared_ptr<FileStream> fs{new FileStream{path}};

	/* 加上 ios_base::trunc，这样打开文件流后，如果原本存在此文件，就会将其截断，
	 * 让其初始长度变成 0，相当于一个新文件。
	 */
	fs->_fs = std::shared_ptr<std::fstream>{
		new std::fstream{
			path,
			std::ios_base::out | std::ios_base::in | std::ios_base::trunc | std::ios_base::binary,
		},
	};

	if (fs->_fs->fail())
	{
		throw std::runtime_error{CODE_POS_STR + std::format("创建 {} 失败。检查文件是不是只读的。", path)};
	}

	fs->_can_read = true;
	fs->_can_write = true;
	fs->_can_seek = true;
	return fs;
}

std::shared_ptr<base::FileStream> base::FileStream::OpenExisting(std::string path)
{
	if (!std::filesystem::exists(path))
	{
		// 文件不存在
		throw std::runtime_error{CODE_POS_STR + std::format("文件 {} 不存在。", path)};
	}

	if (std::filesystem::is_directory(path))
	{
		throw std::runtime_error{CODE_POS_STR + std::format("{} 不是一个文件，而是一个目录", path)};
	}

	std::shared_ptr<FileStream> fs{new FileStream{path}};

	fs->_fs = std::shared_ptr<std::fstream>{
		new std::fstream{
			path,
			std::ios_base::in | std::ios_base::out | std::ios_base::binary,
		},
	};

	if (fs->_fs->fail())
	{
		throw std::runtime_error{CODE_POS_STR + std::format("打开 {} 失败。检查文件是不是只读的。", path)};
	}

	fs->_can_read = true;
	fs->_can_write = true;
	fs->_can_seek = true;
	return fs;
}

std::shared_ptr<base::FileStream> base::FileStream::OpenReadOnly(std::string path)
{
	if (!std::filesystem::exists(path))
	{
		// 文件不存在
		throw std::runtime_error{CODE_POS_STR + std::format("文件 {} 不存在。", path)};
	}

	if (std::filesystem::is_directory(path))
	{
		throw std::runtime_error{CODE_POS_STR + std::format("{} 不是一个文件，而是一个目录", path)};
	}

	std::shared_ptr<FileStream> fs{new FileStream{path}};

	fs->_fs = std::shared_ptr<std::fstream>{
		new std::fstream{
			path,
			std::ios_base::in | std::ios_base::binary,
		},
	};

	if (fs->_fs->fail())
	{
		throw std::runtime_error{CODE_POS_STR + std::format("打开 {} 失败。检查文件是不是只读的。", path)};
	}

	fs->_can_read = true;
	fs->_can_write = false;
	fs->_can_seek = true;
	return fs;
}

base::FileStream::FileStream(std::string path)
{
	_path = path;
}

base::FileStream::~FileStream()
{
	Close();
}

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

#endif // HAS_THREAD
