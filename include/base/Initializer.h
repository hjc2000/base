#pragma once
#include <functional>
#include <vector>

namespace base
{
	/// @brief 初始化器。
	class Initializer
	{
	private:
		/// @brief 获取储存初始化函数的向量。
		/// @return 返回向量的引用。
		static std::vector<std::function<void()>> &InitFunctionVector();

	public:
		/// @brief 构造函数。会将传进来的初始化函数添加到向量中。
		/// @note 当需要初始化时，可以定义一个本类的全局对象，并在构造函数中传入执行初始化逻辑的
		/// lambda 表达式，这样初始化逻辑就会被放入初始化函数向量中。
		/// @note 通过这种方式，初始化函数被放到初始化向量中的顺序是不确定的，所以不要有依赖于调用顺序
		/// 的初始化函数。如果某个初始化函数要求依赖先被初始化，它应该自己在自己内部去初始化，而不应该
		/// 依靠本类，期望本类能够按顺序执行初始化。
		///
		/// @param init_func
		Initializer(std::function<void()> init_func);

		/// @brief 遍历初始化向量，执行里面的所有初始化函数。
		/// @note 应该在 main 函数的开始处执行，确保初始化完成了才可以开始业务逻辑。
		static void Initialize();
	};
}
