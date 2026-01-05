#pragma once
#include "base/stream/Stream.h"
#include "Path.h"
#include <memory>

namespace base::file
{
	///
	/// @brief 先尝试打开文件。如果不存在会创建。
	///
	/// @param path
	///
	/// @return
	///
	std::shared_ptr<base::Stream> OpenOrCreate(base::Path const &path);

	///
	/// @brief 以只读方式打开文件。文件必须存在，否则会抛出异常。
	///
	/// @param path 文件的路径。
	///
	/// @return 成功打开则返回 base::Stream 对象。失败会抛出异常，不会返回空指针。
	///
	std::shared_ptr<base::Stream> OpenReadOnly(base::Path const &path);

	///
	/// @brief 用打开模式打开一个存在的文件。如果文件不存在，此函数不会创建文件。
	///
	/// @param path 文件路径
	///
	/// @return 如果文件存在，且成功打开，则返回 base::Stream 对象。
	/// 失败会抛出异常，不会返回空指针。
	///
	std::shared_ptr<base::Stream> OpenExisting(base::Path const &path);

	///
	/// @brief 用创建模式打开文件流，无论如何都会创建一个新的空白文件。会覆盖旧的。
	///
	/// @param path 文件路径。
	///
	/// @return 创建文件成功则返回 base::Stream 对象。创建失败会抛出异常，不会返回空指针。
	///
	std::shared_ptr<base::Stream> CreateNewAnyway(base::Path const &path);

} // namespace base::file
