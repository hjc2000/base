#include "base/file/filesystem.h"
#include "base/file/Path.h"
#include "base/math/Fraction.h"
#include "base/wrapper/number-wrapper.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include <stdlib.h>

int main()
{
	{
		base::Fraction f{base::Double{std::numbers::pi}};
		std::cout << "分数: " << f << std::endl;

		std::cout << "std::numbers::pi: \t\t"
				  << std::setprecision(17)
				  << std::numbers::pi
				  << std::endl;

		std::cout << "分数表示的 pi 转为 double: \t"
				  << std::setprecision(17)
				  << static_cast<double>(f)
				  << std::endl;

		std::cout << "误差: "
				  << std::setprecision(17)
				  << static_cast<double>(f) - std::numbers::pi
				  << std::endl;
	}

	{
		base::Path path{"C:/Users/huang/disk/ti600_2TB/.temp/mediacreationtool.exe"};

		base::filesystem::Move(path,
							   "C:/Users/huang/disk/ti600_2TB/.temp/a.exe",
							   base::filesystem::OverwriteOption::Update);

		std::cout << path.ParentPath() << std::endl;
	}
}
