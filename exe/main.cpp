#include "base/file/filesystem.h"
#include "base/file/Path.h"
#include "base/math/Fraction.h"
#include "base/wrapper/number-wrapper.h"
#include <cmath>
#include <cstdint>
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
		base::Path input_path{"D:/software/网易云音乐数据/22"};
		base::Path output_path{"D:/software/网易云音乐数据/out"};

		uint64_t count = 0;
		for (base::DirectoryEntry const &entry : base::filesystem::RecursiveDirectoryEntryEnumerable{input_path})
		{
			base::Path dst_path = entry.Path();
			dst_path.RemoveBasePath(input_path);
			dst_path.SetLastName(std::to_string(count++) + '.' + dst_path.ExtensionName());
			dst_path = output_path + dst_path;
			std::cout << dst_path << std::endl;

			base::filesystem::Move(entry.Path(),
								   dst_path,
								   base::filesystem::OverwriteOption::Skip);
		}

		std::cout << "count: " << count << std::endl;
	}
}
