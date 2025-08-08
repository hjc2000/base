#pragma once

namespace base
{
	///
	/// @brief 数据源接口。
	///
	template <typename T>
	class ISource
	{
	public:
		virtual ~ISource() = default;

		///
		/// @brief 从源中读取数据
		///
		/// @param data 这里传入的是引用。派生类可以修改 data。
		///
		/// @return 成功返回 true, 返回 false 则说明数据耗尽（可以是暂时耗尽，需要送入新数据加工后
		/// 才能继续产生输出数据，也可以是永久耗尽）。
		///
		/// 	@note 其他错误应该通过抛出异常的方式传递而不是隐藏起错误然后返回 false.
		///
		virtual bool ReadData(T &data) = 0;
	};

} // namespace base
