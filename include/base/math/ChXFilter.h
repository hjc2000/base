#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

namespace base
{
#pragma region 参数类

    /// @brief 偏差乘上的系数
    class ChXFilter_KError
    {
    private:
        double _value = 0;

    public:
        /// @brief 偏差乘上的系数
        /// @param value
        explicit ChXFilter_KError(double value)
        {
            _value = value;
        }

        double Value() const
        {
            return _value;
        }
    };

    /// @brief 输出值除以该值后才成为反馈值
    class ChXFilter_FeedbackDiv
    {
    private:
        double _value = 0;

    public:
        /// @brief 输出值除以该值后才成为反馈值
        /// @param value
        explicit ChXFilter_FeedbackDiv(double value)
        {
            _value = value;
        }

        double Value() const
        {
            return _value;
        }
    };

#pragma endregion

    /// @brief 利用负反馈的积分环节形成惯性环节。采用的是先对积分环节做差分近似，
    /// 然后用迭代形成闭环。
    class ChXFilter
    {
    private:
        double _k_error = 0;
        double _feedback_div = 1;
        double _current_output = 0;

    public:
        ChXFilter(ChXFilter_KError const &k_error, ChXFilter_FeedbackDiv const &feedback_div);

        /// @brief 输入一个值，并获取反馈输出。
        /// @param x
        /// @return
        double Input(double x);

        /// @brief 反馈输出。
        /// @return
        double Feedback() const
        {
            return _current_output / _feedback_div;
        }

        /// @brief 设置当前的反馈值。
        /// @param value
        /// @return
        void SetFeedback(double value)
        {
            _current_output = value * _feedback_div;
        }

        /// @brief 惯性时间常数
        /// @param sample_interval
        /// @return
        double TimeConstant(double sample_interval);
    };

#if HAS_THREAD
    void Test_ChXFilter();
#endif
} // namespace base
