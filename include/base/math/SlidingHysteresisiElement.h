#pragma once
#include "base/math/HysteresisElement.h"

namespace base
{
	class SlidingHysteresisiElement
	{
	private:
		HysteresisElement _hys;

	public:
		/// @brief 迟滞特性环节。
		/// @param rising_threshold 上升阈值。
		/// @param fallen_threshold 下降阈值。
		SlidingHysteresisiElement(HysteresisElement_RisingThreshold const &rising_threshold,
								  HysteresisElement_FallenThreshold const &fallen_threshold);

		/// @brief 上升阈值。
		/// @return
		double RisingThreshold() const
		{
			return _hys.RisingThreshold();
		}

		void SetRisingThreshold(double value)
		{
			_hys.SetRisingThreshold(value);
		}

		/// @brief 下降阈值。
		/// @return
		double FallenThreshold() const
		{
			return _hys.FallenThreshold();
		}

		void SetFallenThreshold(double value)
		{
			_hys.SetFallenThreshold(value);
		}

		/// @brief 改变上升阈值和下降阈值。
		/// @note 会导致输出发生变化。
		/// @param rising_threshold 上升阈值
		/// @param fallen_threshold 下降阈值
		void ChangeThreshold(HysteresisElement_RisingThreshold const &rising_threshold,
							 HysteresisElement_FallenThreshold const &fallen_threshold)
		{
			_hys.ChangeThreshold(rising_threshold, fallen_threshold);
		}

		/// @brief 上升阈值减去下降阈值，得到的窗口宽度。
		/// @return
		double WindowWidth() const
		{
			return _hys.WindowWidth();
		}

		/// @brief 将窗口在 x 轴上平移。
		/// @param delta_x 位移。负数则窗口向左移动，正数则窗口向右移动。
		void MoveX(double delta_x)
		{
			_hys.MoveX(delta_x);
		}

		/// @brief 向迟滞特性环节输入一个值，并获取该值引起的输出。
		/// @param x
		/// @return
		bool Input(double x);

		/// @brief 当前的输入值。
		/// @return
		double CurrentInput()
		{
			return _hys.CurrentInput();
		}

		/// @brief 当前输出值。
		/// @return
		bool CurrentOutput() const
		{
			return _hys.CurrentOutput();
		}

		/// @brief 检查最近一次输入后输出的变化情况。
		/// @return
		HysteresisElement_OutputChange OutputChange() const
		{
			return _hys.OutputChange();
		}
	};
} // namespace base
