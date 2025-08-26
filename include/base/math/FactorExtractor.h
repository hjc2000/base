#pragma once
#include "base/math/math.h"
#include <limits>
#include <type_traits>

namespace base
{
	template <typename T>
		requires(std::is_integral_v<T>)
	class FactorExtractor
	{
	private:
		T _factor{};
		T _base{};

	public:
		constexpr FactorExtractor() = default;

		constexpr FactorExtractor(T value)
		{
			_factor = 1;
			_base = value;
		}

		constexpr FactorExtractor(T factor, T base)
		{
			_factor = factor;
			_base = base;
		}

		///
		/// @brief 因数。
		///
		/// @return
		///
		constexpr T Factor() const
		{
			return _factor;
		}

		///
		/// @brief 基数。
		///
		/// @return
		///
		constexpr T Base() const
		{
			return _base;
		}

		///
		/// @brief 值 = 因数 * 基数。
		///
		/// @return
		///
		constexpr T Value() const
		{
			return _factor * _base;
		}

		///
		/// @brief 如果 Base 是 factor 的倍数，则进一步将 factor 从 Base
		/// 提取到 Factor 中。
		///
		/// @param factor
		///
		constexpr void ExtractGreedily(T factor)
		{
			ExtractGreedily(factor, std::numeric_limits<T>::max());
		}

		///
		/// @brief 如果 Base 是 factor 的倍数，则进一步将 factor 从 Base
		/// 提取到 Factor 中。但是 Factor 的大小是有限制的，Factor 的绝对值
		/// 不会大于 factor_limit 的绝对值。
		///
		/// @param factor
		/// @param factor_limit
		///
		constexpr void ExtractGreedily(T factor, T factor_limit)
		{
			while (base::abs(_base) >= base::abs(factor) &&
				   _base % factor == 0)
			{
				if (base::abs(_factor) > base::abs(factor_limit / factor))
				{
					break;
				}

				_base /= factor;
				_factor *= factor;
			}
		}

		constexpr void ConservativeExtract(T factor, T factor_limit)
		{
			while (base::abs(_base) >= base::abs(factor) &&
				   _base % factor == 0)
			{
				if (base::abs(_factor) > base::abs(factor_limit / factor))
				{
					break;
				}

				_base /= factor;
				_factor *= factor;
			}
		}
	};

} // namespace base
