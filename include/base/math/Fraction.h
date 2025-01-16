#pragma once
#include <base/string/ICanToString.h>
#include <ostream>
#include <stdint.h>
#include <string>

namespace base
{
	/// @brief 分数类
	class Fraction final :
		public base::ICanToString
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
#pragma endregion

		int64_t Num() const;
		void SetNum(int64_t value);

		int64_t Den() const;
		void SetDen(int64_t value);

		/// @brief 化简分数，返回化简后的值。
		/// @return
		Fraction Simplify() const;

		/// @brief 倒数
		/// @return
		Fraction Reciprocal() const;

		/// @brief 向下取整
		/// @return
		int64_t Floor() const;

		/// @brief 向上取整
		/// @return
		int64_t Ceil() const;

		Fraction operator-() const;
		Fraction operator+(Fraction const &value) const;
		Fraction operator-(Fraction const &value) const;
		Fraction operator*(Fraction const &value) const;
		Fraction operator/(Fraction const &value) const;

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

		double ToDouble() const;

		/// @brief 将分数转化为字符串
		/// @return
		std::string ToString() const override;

		explicit operator int64_t() const;
		explicit operator double() const;
#pragma endregion

		bool operator==(Fraction const &value) const;
		bool operator<(Fraction const &value) const;
		bool operator>(Fraction const &value) const;
		bool operator<=(Fraction const &value) const;
		bool operator>=(Fraction const &value) const;
	};
} // namespace base

std::ostream &operator<<(std::ostream &ostream, base::Fraction const &right);
base::Fraction operator+(int64_t left, base::Fraction const &right);
base::Fraction operator-(int64_t left, base::Fraction const &right);
base::Fraction operator*(int64_t left, base::Fraction const &right);
base::Fraction operator/(int64_t left, base::Fraction const &right);

namespace std
{
	/// @brief 向下取整
	/// @param value
	/// @return
	int64_t floor(base::Fraction const &value);

	/// @brief 向上取整
	/// @param value
	/// @return
	int64_t ceil(base::Fraction const &value);
} // namespace std
