#pragma once
#include "base/stream/Stream.h"
#include <memory>

#if HAS_THREAD

namespace base
{
	///
	/// @brief 获取标准输出流实例。
	///
	/// @return
	///
	std::shared_ptr<base::Stream> std_out_stream();

} // namespace base

#endif // HAS_THREAD
