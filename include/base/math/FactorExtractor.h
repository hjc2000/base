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
		/// @brief 贪心地提取因数。
		///
		/// @note 只要基数还能提取因数，就不断把因数提取到 Factor 中。除非提取会让 Factor
		/// 超过限制值。
		///
		/// @param factor
		///
		constexpr void ExtractGreedily(T factor)
		{
			ExtractGreedily(factor, std::numeric_limits<T>::max());
		}

		///
		/// @brief 贪心地提取因数。
		///
		/// @note 只要基数还能提取因数，就不断把因数提取到 Factor 中。除非提取会让 Factor
		/// 超过限制值。
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

		///
		/// @brief 保守地提取因数。
		///
		/// @note 只要基数不大于限制值，就停止提取。
		///
		/// @param factor
		/// @param base_limit
		///
		constexpr void ExtractConservatively(T factor)
		{
			ExtractConservatively(factor, std::numeric_limits<T>::max());
		}

		///
		/// @brief 保守地提取因数。
		///
		/// @note 只要基数不大于限制值，就停止提取。
		///
		/// @param factor
		/// @param base_limit
		///
		constexpr void ExtractConservatively(T factor, T base_limit)
		{
			while (base::abs(_base) > base::abs(base_limit) &&
				   _base % factor == 0)
			{
				_base /= factor;
				_factor *= factor;
			}
		}
	};

} // namespace base
