#pragma once
#include "base/container/Set.h"
#include "base/filesystem/file.h"
#include "base/math/random.h"
#include "base/stream/StreamWriter.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <functional>
#include <memory>

namespace base::usage
{
	///
	/// @brief 运算符。
	///
	///
	enum class Operator
	{
		Add,
		Sub,
		Mul,
		Div,
	};

	///
	/// @brief 计算题。
	///
	///
	class CalculationQuestion :
		public base::ICanToString
	{
	private:
		int32_t _left{};
		int32_t _right{};
		base::usage::Operator _operator{};

	public:
		CalculationQuestion(int32_t left, int32_t right, base::usage::Operator op)
		{
			_left = left;
			_right = right;
			_operator = op;
		}

		int32_t Left() const
		{
			return _left;
		}

		int32_t Right() const
		{
			return _right;
		}

		base::usage::Operator Operator() const
		{
			return _operator;
		}

		int32_t Result() const
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

		///
		/// @brief 转化为字符串
		///
		/// @return
		///
		virtual std::string ToString() const override
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
	};

	///
	/// @brief 计算题生成器。
	///
	///
	class CalculationQuestionGenerator
	{
	private:
		int32_t _min{};
		int32_t _max{};
		base::usage::Operator _operator{};
		std::function<bool(base::usage::CalculationQuestion const &)> _filter{};
		std::shared_ptr<base::IRandomGenerator> _random_generator;

	public:
		CalculationQuestionGenerator(int32_t min,
									 int32_t max,
									 base::usage::Operator op,
									 std::function<bool(base::usage::CalculationQuestion const &)> filter)
			: _min(min),
			  _max(max),
			  _operator(op),
			  _filter(filter)
		{
			_random_generator = base::CreateRandomGenerator();
		}

		base::usage::CalculationQuestion Generate() const
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
	};

	///
	/// @brief 生成计算题。
	///
	inline void GenerateCalculationQuestions()
	{
		std::shared_ptr<base::Stream> fs = base::file::CreateNewAnyway("math.txt");
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

} // namespace base::usage
