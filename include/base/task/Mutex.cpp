#include "Mutex.h"

base::task::Mutex::Mutex()
	: _handle(base::task::create_mutex())
{
	// 将实现放到源文件中预编译，可以防止有些卧龙凤雏的库，定义了一个宏名为
	// create_mutex, 导致我无法正确调用 base::task::create_mutex 函数。
}
