#include "base/math/Fraction.h"
#include "base/task/delay.h"
#include "base/task/ThreadPool.h"
#include "base/wrapper/number-wrapper.h"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <stdlib.h>

int main()
{
	{
		base::Fraction f{base::Double{std::numbers::pi}};
		constexpr int precision = 512;

		std::cout << "分数: " << f << std::endl;

		std::cout << "std::numbers::pi: \t\t"
				  << std::setprecision(precision)
				  << std::numbers::pi
				  << std::endl;

		std::cout << "分数表示的 pi 转为 double: \t"
				  << std::setprecision(precision)
				  << static_cast<double>(f)
				  << std::endl;

		std::cout << "误差: "
				  << std::setprecision(precision)
				  << static_cast<double>(f) - std::numbers::pi
				  << std::endl;
	}

	{
		base::task::ThreadPool pool{2};

		pool.Run([&]()
				 {
					 while (!pool.Disposed())
					 {
						 std::cout << "66666666666666666666" << std::endl;
						 base::task::Delay(std::chrono::milliseconds{1000});
					 }
				 });

		pool.Run([&]()
				 {
					 while (!pool.Disposed())
					 {
						 std::cout << "77777777777777777777" << std::endl;
						 base::task::Delay(std::chrono::milliseconds{1000});
					 }
				 });

		std::cin.get();
		pool.Dispose();
	}
}
