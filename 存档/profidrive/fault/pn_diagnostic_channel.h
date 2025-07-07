#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

	///
	/// @brief 向 PN 的诊断通道添加一个错误。
	///
	/// @param diagnostic_tag profidrive 使用一个标签来作为错误的标识，后续移除错误依赖
	/// 该标识。类似于 std::map 中的 key.
	///
	/// @param fault_class profidrive 中定义的错误类。
	///
	void pn_diagnostic_channel_add_fault(uint32_t diagnostic_tag, uint32_t fault_class);

	///
	/// @brief 从 PN 的诊断通道中移除一个错误。
	///
	/// @param diagnostic_tag profidrive 使用一个标签来作为错误的标识，后续移除错误依赖
	/// 该标识。类似于 std::map 中的 key.
	///
	/// @param fault_class profidrive 中定义的错误类。
	///
	void pn_diagnostic_channel_remove_fault(uint32_t diagnostic_tag, uint32_t fault_class);

#ifdef __cplusplus
}
#endif
