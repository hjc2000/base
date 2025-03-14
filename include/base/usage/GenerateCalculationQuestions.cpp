#if HAS_THREAD
	#include "GenerateCalculationQuestions.h"
	#include <base/math/IRandomGenerator.h>
	#include <base/stream/IFileStream.h>
	#include <base/stream/StreamWriter.h>
	#include <format>

void base::usage::GenerateCalculationQuestions(int32_t min, int32_t max)
{
	std::shared_ptr<base::IFileStream> fs = base::di::file::CreateNewAnyway("math.txt");
	base::StreamWriter writer{fs};
	std::shared_ptr<base::IRandomGenerator> random_generator = base::di::CreateRandomGenerator();

	int32_t count = 0;
	while (count <= 24)
	{
		int32_t left = random_generator->GenerateUInt32Random(min, max);
		int32_t right = random_generator->GenerateUInt32Random(min, max);
		int32_t op = random_generator->GenerateUInt32Random(0, 1);
		char op_char = '+';
		if (op)
		{
			op_char = '-';
		}

		int32_t sum = 0;
		if (op == 0)
		{
			sum = left + right;
		}
		else
		{
			sum = left - right;
		}

		if (left == right && op == 1)
		{
			continue;
		}

		if (sum < 0 || sum > 99)
		{
			continue;
		}

		std::string equ = std::format("{} {} {} =",
									  left, op_char, right);

		while (equ.size() < 35)
		{
			equ += ' ';
		}

		equ += std::to_string(sum);
		std::cout << equ << std::endl;
		writer.WriteLine(equ);
		writer.WriteLine();
		count++;
	}
}

void base::usage::GenerateCalculationQuestions()
{
	GenerateCalculationQuestions(2, 20);
}
#endif
