#pragma once

namespace base
{
	///
	/// @brief 利用负反馈的积分环节形成惯性环节。采用的是先对积分环节做差分近似，
	/// 然后用迭代形成闭环。
	///
	template <typename T>
	class FeedbackInertialElement
	{
	private:
		T _k_error = 0;
		T _feedback_div = 1;
		T _current_output = 0;

	public:
		/* #region 参数类 */

		///
		/// @brief 偏差乘上的系数
		///
		///
		class KError_t
		{
		private:
			T _value = 0;

		public:
			///
			/// @brief 偏差乘上的系数
			///
			/// @param value
			///
			constexpr explicit KError_t(T value)
			{
				_value = value;
			}

			constexpr T Value() const
			{
				return _value;
			}
		};

		///
		/// @brief 输出值除以该值后才成为反馈值
		///
		///
		class FeedbackDiv_t
		{
		private:
			T _value = 0;

		public:
			///
			/// @brief 输出值除以该值后才成为反馈值
			///
			/// @param value
			///
			constexpr explicit FeedbackDiv_t(T value)
			{
				_value = value;
			}

			constexpr T Value() const
			{
				return _value;
			}
		};

		/* #endregion */

		constexpr FeedbackInertialElement(base::FeedbackInertialElement<T>::KError_t const &k_error,
										  base::FeedbackInertialElement<T>::FeedbackDiv_t const &feedback_div)
		{
			_k_error = k_error.Value();
			_feedback_div = feedback_div.Value();
		}

		constexpr T KError() const
		{
			return _k_error;
		}

		constexpr void SetKError(T value)
		{
			_k_error = value;
		}

		constexpr T FeedbackDiv() const
		{
			return _feedback_div;
		}

		constexpr void SetFeedbackDiv(T value)
		{
			_feedback_div = value;
		}

		constexpr void ChangeParameter(base::FeedbackInertialElement<T>::KError_t const &k_error,
									   base::FeedbackInertialElement<T>::FeedbackDiv_t const &feedback_div)
		{
			_k_error = k_error.Value();
			_feedback_div = feedback_div.Value();
		}

		///
		/// @brief 输入一个值，并获取反馈输出。
		///
		/// @param x
		///
		/// @return
		///
		constexpr T Input(T x)
		{
			T error = x - Feedback();
			_current_output += error * _k_error;
			return Feedback();
		}

		///
		/// @brief 反馈输出。
		///
		/// @return
		///
		constexpr T Feedback() const
		{
			return _current_output / _feedback_div;
		}

		///
		/// @brief 设置当前的反馈值。
		///
		/// @param value
		///
		/// @return
		///
		constexpr void SetFeedback(T value)
		{
			_current_output = value * _feedback_div;
		}

		///
		/// @brief 惯性时间常数
		///
		/// @param sample_interval
		///
		/// @return
		///
		constexpr T TimeConstant(T sample_interval)
		{
			//
			// 		k_error = (sample_interval * k) / T1
			// 		k_error = sample_interval * (k / T1)
			//
			// 则
			//
			// 		k / T1 = k_error / sample_interval
			// 		T1 / k = sample_interval / k_error
			//
			// 惯性时间常数为
			//
			// 		T1 / (k * kb)
			//		= (T1 / k) / kb
			//		= (T1 / k) * feedback_div
			//		= sample_interval / k_error * feedback_div
			//
			return sample_interval * _feedback_div / _k_error;
		}
	};

#if HAS_THREAD
	void Test_ChXFilter();
#endif
} // namespace base
