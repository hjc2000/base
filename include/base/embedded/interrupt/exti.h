#pragma once

namespace base
{
	namespace exti
	{
		///
		/// @brief 注册使用一条外部中断线。
		///
		/// @warning 实现者在实现函数时应该注意禁用中断，防止竞态。
		///
		/// @param line_id 中断线的 id
		/// @param callback 发生中断时的回调函数
		///
		void register_callback(int line_id, std::function<void()> const &callback);

		///
		/// @brief 注销一条外部中断线的使用。
		///
		/// @warning 实现者在实现函数时应该注意禁用中断，防止竞态。
		///
		/// @param line_id 中断线的 id
		///
		void unregister_callback(int line_id);

	} // namespace exti
} // namespace base
