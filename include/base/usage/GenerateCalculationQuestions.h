#pragma once
#include "base/math/random.h"
#include "base/string/ICanToString.h"
#include <cstdint>
#include <functional>
#include <memory>

#if HAS_THREAD

namespace base
{
	namespace usage
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
			CalculationQuestion(int32_t left, int32_t right, base::usage::Operator op);

			int32_t Left() const;

			int32_t Right() const;

			base::usage::Operator Operator() const;

			int32_t Result() const;

			/**
			 * @brief 转化为字符串
			 *
			 * @return std::string
			 */
			virtual std::string ToString() const override;
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
										 std::function<bool(base::usage::CalculationQuestion const &)> filter);

			base::usage::CalculationQuestion Generate() const;
		};

		///
		/// @brief 生成计算题。
		///
		///
		void GenerateCalculationQuestions();
	} // namespace usage
} // namespace base
#endif
