#pragma once

namespace base
{
	/// @brief 线性插值器的起始值
	class LinearInterpolator_StartVlaue
	{
	private:
		double _value = 0;

	public:
		explicit LinearInterpolator_StartVlaue(double value)
		{
			_value = value;
		}

		double Value() const
		{
			return _value;
		}
	};

	/// @brief 线性插值器的起始值
	class LinearInterpolator_EndVlaue
	{
	private:
		double _value = 0;

	public:
		explicit LinearInterpolator_EndVlaue(double value)
		{
			_value = value;
		}

		double Value() const
		{
			return _value;
		}
	};

	/// @brief 线性插值器的步数。
	class LinearInterpolator_StepCount

	{
	private:
		int _value = 0;

	public:
		explicit LinearInterpolator_StepCount(int value)
		{
			_value = value;
		}

		int Value() const
		{
			return _value;
		}
	};

	/// @brief 线性插值器的步长
	class LinearInterpolator_StepLength
	{
	private:
		double _value = 0;

	public:
		explicit LinearInterpolator_StepLength(double value)
		{
			_value = value;
		}

		double Value() const
		{
			return _value;
		}
	};

	/// @brief 线性插值器
	class LinearInterpolator final
	{
	private:
		double _start_value = 0;
		double _end_value = 0;
		double _step_length = 0;
		double _current_value = 0;

	public:
		LinearInterpolator(LinearInterpolator_StartVlaue const &start_value,
						   LinearInterpolator_EndVlaue const &end_value,
						   LinearInterpolator_StepLength const &step_length);

		LinearInterpolator(LinearInterpolator_StartVlaue const &start_value,
						   LinearInterpolator_EndVlaue const &end_value,
						   LinearInterpolator_StepCount const &step_count);

		double StartValue() const
		{
			return _start_value;
		}

		double EndValue() const
		{
			return _end_value;
		}

		void SetEndValue(double value)
		{
			_end_value = value;
		}

		double StepLength() const
		{
			return _step_length;
		}

		bool IsCompleted() const;

		double CurrentValue() const
		{
			return _current_value;
		}

		/// @brief 前缀递增
		/// @return
		double operator++();

		/// @brief 后缀递增
		/// @param
		/// @return
		double operator++(int);
	};
} // namespace base
