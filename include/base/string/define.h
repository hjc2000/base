#pragma once

/* 将传进来的代码文本变成字符串。
 * 例如
 * 		DEFINE_TO_STR(hello)
 * 会被展开成代码
 * 		"hello"
 * 相当于你在展开位置写了一个 "hello" 字面量。
 */
#define DEFINE_TO_STR(x) #x

/* 将传进来的宏定义的值变成字符串。
 * 例如已经定义了一个宏
 *  	#define NUM 1
 * 使用
 * 		DEFINE_VALUE_TO_STR(NUM)
 * NUM 首先会被展开，相当于
 * 		DEFINE_VALUE_TO_STR(1)
 * 接着 DEFINE_VALUE_TO_STR 又被展开，相当于
 * 		DEFINE_TO_STR(1)
 * 于是得到字符串字面量
 * 		"1"
 * 相当于你直接在展开的位置写下了 "1" 这样的代码。
 */
#define DEFINE_VALUE_TO_STR(x) DEFINE_TO_STR(x)

#ifdef __cplusplus
	#include <string> // IWYU pragma: keep

	#define CODE_POS_STR std::string{"文件：" __FILE__ ", 行号：" DEFINE_VALUE_TO_STR(__LINE__)} + \
							 std::string{", 函数："} + std::string{__func__} +                     \
							 " >>\n"
#else // #ifdef __cplusplus
	#define CODE_POS_STR "文件：" __FILE__ ", 行号：" DEFINE_VALUE_TO_STR(__LINE__) " >>\n"
#endif // #ifdef __cplusplus
