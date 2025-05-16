#pragma once
#include <cstdint>
#include <functional>

namespace base
{
	namespace exti
	{
		///
		/// @brief EXTI 中断默认使用的优先级。
		///
		/// @return
		///
		int32_t default_priority();

		///
		/// @brief 设置 EXTI 中断默认使用的优先级。
		///
		/// @param priority
		///
		void set_default_priority(int32_t priority);

		///
		/// @brief 注册 EXTI 中断回调。
		///
		/// @param line_id 中短线的 ID.
		/// @param priority 中断优先级。
		/// @param callback 回调函数。
		///
		void register_callback(int32_t line_id,
							   int32_t priority,
							   std::function<void()> const &callback);

		///
		/// @brief 注册使用一条外部中断线。
		///
		/// @warning 实现者在实现函数时应该注意禁用中断，防止竞态。
		///
		/// @param line_id 中断线的 id
		/// @param callback 发生中断时的回调函数
		///
		void register_callback(int32_t line_id, std::function<void()> const &callback);

		///
		/// @brief 注销一条外部中断线的使用。
		///
		/// @warning 实现者在实现函数时应该注意禁用中断，防止竞态。
		///
		/// @param line_id 中断线的 id
		///
		void unregister_callback(int32_t line_id);

	} // namespace exti
} // namespace base
