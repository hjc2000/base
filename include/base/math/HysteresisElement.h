#pragma once

namespace base
{
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

    public:
        HysteresisElement(double rising_threshold, double fallen_threshold)
        {
            _rising_threshold = rising_threshold;
            _fallen_threshold = fallen_threshold;
        }

        double RisingThreshold() const
        {
            return _rising_threshold;
        }

        double FallenThreshold() const
        {
            return _fallen_threshold;
        }

        double WindowWidth() const
        {
            return _rising_threshold - _fallen_threshold;
        }

        void MoveX(double delta_x)
        {
            _rising_threshold += delta_x;
            _fallen_threshold += delta_x;
        }

        bool Input(double x);

        bool CurrentOutput() const
        {
            return _current_output;
        }

        /// @brief 检查最近一次输入后输出的变化情况。
        /// @return
        HysteresisElement_OutputChange OutputChange();
    };
} // namespace base
