#pragma once

namespace base
{
	/// @brief 上升阈值
	class HysteresisElement_RisingThreshold
	{
	private:
		double _value = 0;

	public:
		/// @brief 上升阈值
		/// @param value
		explicit HysteresisElement_RisingThreshold(double value)
		{
			_value = value;
		}

		double Value() const
		{
			return _value;
		}
	};

	/// @brief 下降阈值
	class HysteresisElement_FallenThreshold
	{
	private:
		double _value = 0;

	public:
		/// @brief 下降阈值
		/// @param value
		explicit HysteresisElement_FallenThreshold(double value)
		{
			_value = value;
		}

		double Value() const
		{
			return _value;
		}
	};

	/// @brief 输出的变化
	enum class HysteresisElement_OutputChange
	{
		None,
		Rise,
		Fall,
	};

	/// @brief 迟滞特性环节。
	class HysteresisElement final
	{
	private:
		double _rising_threshold = 0;
		double _fallen_threshold = 0;
		bool _current_output = false;
		bool _last_output = false;
		double _x = 0;

	public:
		/// @brief 迟滞特性环节。
		/// @param rising_threshold 上升阈值。
		/// @param fallen_threshold 下降阈值。
		HysteresisElement(HysteresisElement_RisingThreshold const &rising_threshold,
						  HysteresisElement_FallenThreshold const &fallen_threshold);

		/// @brief 上升阈值。
		/// @return
		double RisingThreshold() const
		{
			return _rising_threshold;
		}

		void SetRisingThreshold(double value)
		{
			_rising_threshold = value;
		}

		/// @brief 下降阈值。
		/// @return
		double FallenThreshold() const
		{
			return _fallen_threshold;
		}

		void SetFallenThreshold(double value)
		{
			_fallen_threshold = value;
		}

		/// @brief 改变上升阈值和下降阈值。
		/// @note 会导致输出发生变化。
		/// @param rising_threshold 上升阈值
		/// @param fallen_threshold 下降阈值
		void ChangeThreshold(HysteresisElement_RisingThreshold const &rising_threshold,
							 HysteresisElement_FallenThreshold const &fallen_threshold);

		/// @brief 上升阈值减去下降阈值，得到的窗口宽度。
		/// @return
		double WindowWidth() const
		{
			return _rising_threshold - _fallen_threshold;
		}

		/// @brief 将窗口在 x 轴上平移。
		/// @param delta_x 位移。负数则窗口向左移动，正数则窗口向右移动。
		void MoveX(double delta_x)
		{
			_rising_threshold += delta_x;
			_fallen_threshold += delta_x;
		}

		/// @brief 向迟滞特性环节输入一个值，并获取该值引起的输出。
		/// @param x
		/// @return
		bool Input(double x);

		/// @brief 当前的输入值。
		/// @return
		double CurrentInput()
		{
			return _x;
		}

		/// @brief 当前输出值。
		/// @return
		bool CurrentOutput() const
		{
			return _current_output;
		}

		/// @brief 检查最近一次输入后输出的变化情况。
		/// @return
		HysteresisElement_OutputChange OutputChange() const;
	};
} // namespace base
