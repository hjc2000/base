#pragma once
#include <cstdlib>

///
/// @brief 分配特定类型的大小的内存。
///
/// @tparam T
/// @param size
/// @return T*
///
template <typename T>
T *Malloc(size_t size)
{
	return reinterpret_cast<T *>(malloc(size));
}
