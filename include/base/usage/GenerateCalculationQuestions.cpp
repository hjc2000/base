#include "GenerateCalculationQuestions.h"

#if HAS_THREAD
	#include <base/container/Set.h>
	#include <base/file/IFileStream.h>
	#include <base/math/random.h>
	#include <base/stream/StreamWriter.h>

base::usage::CalculationQuestion::CalculationQuestion(int32_t left, int32_t right, base::usage::Operator op)
{
	_left = left;
	_right = right;
	_operator = op;
}

int32_t base::usage::CalculationQuestion::Left() const
{
	return _left;
}

int32_t base::usage::CalculationQuestion::Right() const
{
	return _right;
}

base::usage::Operator base::usage::CalculationQuestion::Operator() const
{
	return _operator;
}

int32_t base::usage::CalculationQuestion::Result() const
{
	switch (_operator)
	{
	case base::usage::Operator::Add:
		{
			return _left + _right;
		}
	case base::usage::Operator::Sub:
		{
			return _left - _right;
		}
	case base::usage::Operator::Mul:
		{
			return _left * _right;
		}
	case base::usage::Operator::Div:
		{
			return _left / _right;
		}
	}

	throw std::runtime_error{CODE_POS_STR + "非法运算符。"};
}

std::string base::usage::CalculationQuestion::ToString() const
{
	char op_char = '+';
	switch (_operator)
	{
	case base::usage::Operator::Add:
		{
			op_char = '+';
			break;
		}
	case base::usage::Operator::Sub:
		{
			op_char = '-';
			break;
		}
	case base::usage::Operator::Mul:
		{
			op_char = '*';
			break;
		}
	case base::usage::Operator::Div:
		{
			op_char = '/';
			break;
		}
	}

	std::string equ = std::format("{} {} {} =",
								  _left, op_char, _right);

	return equ;
}

base::usage::CalculationQuestionGenerator::CalculationQuestionGenerator(int32_t min,
																		int32_t max,
																		base::usage::Operator op,
																		std::function<bool(base::usage::CalculationQuestion const &)> filter)
	: _min(min),
	  _max(max),
	  _operator(op),
	  _filter(filter)
{
	_random_generator = base::di::CreateRandomGenerator();
}

base::usage::CalculationQuestion base::usage::CalculationQuestionGenerator::Generate() const
{
	while (true)
	{
		int32_t left = _random_generator->GenerateUInt32Random(_min, _max);
		int32_t right = _random_generator->GenerateUInt32Random(_min, _max);
		base::usage::CalculationQuestion ret{left, right, _operator};
		if (_filter != nullptr && _filter(ret))
		{
			continue;
		}

		return ret;
	}
}

void base::usage::GenerateCalculationQuestions()
{
	std::shared_ptr<base::IFileStream> fs = base::di::file::CreateNewAnyway("math.txt");
	base::StreamWriter writer{fs};

	std::function<bool(base::usage::CalculationQuestion const &)> filter{
		[](base::usage::CalculationQuestion const &question) -> bool
		{
			if (question.Left() % 10 == 0)
			{
				return true;
			}

			if (question.Right() % 10 == 0)
			{
				return true;
			}

			if (question.Result() % 10 == 0)
			{
				return true;
			}

			if (question.Result() < 0 || question.Result() > 99)
			{
				return true;
			}

			if (question.Operator() == base::usage::Operator::Sub)
			{
				// 减法
				if (question.Left() == question.Right())
				{
					return true;
				}

				if (question.Left() % 10 > question.Right() % 10)
				{
					return true;
				}
			}

			return false;
		}};

	base::usage::CalculationQuestionGenerator generator{
		5,
		31,
		base::usage::Operator::Sub,
		filter,
	};

	base::Set<std::string> questions;
	while (questions.Count() < 24)
	{
		base::usage::CalculationQuestion question = generator.Generate();
		questions.Add(question.ToString());
	}

	base::List<std::string> question_list;
	question_list.Add(questions);
	question_list.Shuffle();
	for (std::string const &question : question_list)
	{
		std::cout << question << std::endl;
		writer.WriteLine(question);
		writer.WriteLine();
	}
}
#endif
