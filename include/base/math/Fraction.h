#pragma once
#include <ostream>
#include <stdint.h>
#include <string>

namespace base
{
	/// @brief 分数类
	class Fraction
	{
	private:
		int64_t _num = 0;
		int64_t _den = 1;

	public:
#pragma region 生命周期
		/// @brief 默认构造，分子为 0，分母为 1.
		Fraction() = default;

		/// @brief 整型转化为分数，则分子等于整型，分母为 1.
		/// @param num
		Fraction(int64_t num);

		/// @brief 通过分子，分母进行构造。
		/// @param num 分子
		/// @param den 分母
		Fraction(int64_t num, int64_t den);

		/// @brief 拷贝构造
		/// @param o
		Fraction(Fraction const &o);

		Fraction &operator=(Fraction const &o);

		/// @brief 将整型赋值给分数，则变为分子为该整型，分母为 1 的分数。
		/// @param o
		/// @return
		Fraction &operator=(int64_t o);
#pragma endregion

		int64_t Num() const;
		void SetNum(int64_t value);

		int64_t Den() const;
		void SetDen(int64_t value);

		/// @brief 化简分数，返回化简后的值。
		/// @return
		Fraction Simplify() const;

		Fraction operator-() const;
		Fraction operator+(Fraction const &value) const;
		Fraction operator-(Fraction const &value) const;
		Fraction operator*(Fraction const &value) const;
		Fraction operator/(Fraction const &value) const;

		/// @brief 倒数
		/// @return
		Fraction Reciprocal() const;

		Fraction &operator+=(Fraction const &value);
		Fraction &operator-=(Fraction const &value);
		Fraction &operator*=(Fraction const &value);
		Fraction &operator/=(Fraction const &value);

#pragma region 强制转换
		/// @brief 获取分子除以分母的值
		/// @return
		int64_t Div() const;

		/// @brief 获取分子除以分母的余数
		/// @return
		int64_t Mod() const;

		double ToDouble();

		/// @brief 将分数转化为字符串
		/// @return
		std::string ToString() const;

		explicit operator int64_t();
		explicit operator double();
		explicit operator std::string();
#pragma endregion
	};
}

std::ostream &operator<<(std::ostream &ostream, base::Fraction const &fraction);
base::Fraction operator+(int64_t left, base::Fraction const &right);
base::Fraction operator-(int64_t left, base::Fraction const &right);
base::Fraction operator*(int64_t left, base::Fraction const &right);
base::Fraction operator/(int64_t left, base::Fraction const &right);
