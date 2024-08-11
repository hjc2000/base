#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#if HAS_THREAD
#include <base/container/IQueue.h>
#include <base/container/SafeQueue.h>
#include <base/IDisposable.h>
#include <base/string/ICanToString.h>
#include <condition_variable>
#include <iostream>
#include <mutex>

namespace base
{
    /// @brief 带有滞回特性的阻塞队列。
    /// @note 队列满时，再往里送会阻塞，直到队列中的元素被消费到小于一定阈值才取消阻塞。
    /// @note 队列空时，再往外拿会阻塞，直到队列中的元素大于一定阈值才取消阻塞。
    /// @note 本队列线程安全。
    ///
    /// @tparam T
    template <typename T>
    class HysteresisBlockingQueue final : public base::IQueue<T>, public base::IDisposable
    {
    private:
        std::atomic_bool _disposed = false;

        /// @brief 为 true 表示被冲洗了。
        /// @note 被冲洗后入队会抛出异常。
        /// @note 被冲洗后出队不会再被阻塞。
        std::atomic_bool _flushed = false;

        /// @brief 队列容量的上限。
        int32_t _max = 0;

        /// @brief 队列元素数量小于此值时取消对入队的阻塞。
        int32_t _threshold = 0;

        base::SafeQueue<T> _queue;

        /// @brief 非私有方法需要加锁。
        std::mutex _not_private_methods_lock;

        /// @brief 队列中元素数量小于阈值时条件成立。
        std::condition_variable _queue_consumed_cv;

        /// @brief 队列中元素数量大于阈值时条件成立。
        std::condition_variable _queue_avaliable_cv;

    public:
        /// @brief 构造函数
        /// @param max 队列能容纳的元素的最大数量。
        HysteresisBlockingQueue(int32_t max)
        {
            using namespace std;
            if (max <= 0)
            {
                throw std::invalid_argument{"最大值不能 <= 0"};
            }

            _max = max;
            _threshold = _max / 2;
        }

        ~HysteresisBlockingQueue()
        {
            Dispose();
        }

        /// @brief 释放
        /// @note 会清空队列。
        /// @note 会取消所有阻塞，并且不再具有阻塞能力。
        void Dispose() override
        {
            if (_disposed)
            {
                return;
            }

            _disposed = true;

            _queue.Clear();
            _queue_consumed_cv.notify_all();
            _queue_avaliable_cv.notify_all();
        }

        /// @brief 队列中当前元素个数
        /// @return
        int32_t Count() const override
        {
            // _queue 线程安全，这里不需要加锁。
            return _queue.Count();
        }

        /// @brief 退队。
        /// @note 队列空了再次尝试退队会受到阻塞，直到队列里的元素数量大于阈值。
        /// @note 在 Dispose 或 Flush 或析构函数执行后，本方法会被无条件取消阻塞，此时如果队列为空，
        /// 会抛出异常。
        ///
        /// @return 退队的元素。
        T Dequeue()
        {
            std::unique_lock<std::mutex> l(_not_private_methods_lock);

            if (_disposed)
            {
                throw std::runtime_error{"此对象已释放，不能再使用"};
            }

            auto p_func = [&]()
            {
                if (_disposed || _flushed)
                {
                    // 释放后和冲洗后不再阻塞
                    return true;
                }

                // 等待直到队列中有元素可以退队。
                return _queue.Count() > 0;
            };
            _queue_avaliable_cv.wait(l, p_func);

            T element = _queue.Dequeue();
            if (_queue.Count() <= _threshold)
            {
                _queue_consumed_cv.notify_all();
            }

            return element;
        }

        /// @brief 尝试退队
        /// @param out
        /// @return 退队成功返回 true，失败返回 false。
        bool TryDequeue(T &out)
        {
            std::unique_lock<std::mutex> l(_not_private_methods_lock);

            if (_disposed)
            {
                throw std::runtime_error{"此对象已释放，不能再使用"};
            }

            auto p_func = [&]()
            {
                if (_disposed || _flushed)
                {
                    // 释放后和冲洗后不再阻塞
                    return true;
                }

                // 等待直到队列中有元素可以退队。
                return _queue.Count() > 0;
            };
            _queue_avaliable_cv.wait(l, p_func);

            bool result = _queue.TryDequeue(out);
            if (result && _queue.Count() <= _threshold)
            {
                _queue_consumed_cv.notify_all();
            }

            return result;
        }

        /// @brief 入队。
        /// @note 如果队列满了会受到阻塞，直到队列元素被消费到小于阈值时才取消阻塞。
        /// @note Dispose 和 Flush 会无条件取消阻塞。但是，Dispose 和 Flush 后，
        /// 再次尝试入队会抛出异常。
        ///
        /// @param obj
        void Enqueue(T obj)
        {
            std::unique_lock<std::mutex> l(_not_private_methods_lock);

            if (_disposed)
            {
                throw std::runtime_error{"此对象已释放，不能再使用"};
            }

            if (_flushed)
            {
                throw std::runtime_error{"队列已冲洗，无法入队。"};
            }

            auto p_func = [&]()
            {
                if (_disposed || _flushed)
                {
                    return true;
                }

                return _queue.Count() < _max;
            };
            _queue_consumed_cv.wait(l, p_func);

            _queue.Enqueue(obj);
            if (_queue.Count() >= _threshold)
            {
                _queue_avaliable_cv.notify_all();
            }
        }

        /// @brief 清空队列
        void Clear()
        {
            if (_disposed)
            {
                throw std::runtime_error{"此对象已释放，不能再使用"};
            }

            _queue.Clear();
            _queue_consumed_cv.notify_all();
        }

        /// @brief 冲洗队列。
        /// @note 冲洗后，再尝试入队会抛出异常。
        /// @note 冲洗后，出队操作将不会被阻塞，即使队列中为空。
        void Flush()
        {
            if (_disposed)
            {
                throw std::runtime_error{"此对象已释放，不能再使用"};
            }

            _flushed = true;
            _queue_consumed_cv.notify_all();
            _queue_avaliable_cv.notify_all();
        }

        /// @brief 检查队列是否已被冲洗。
        /// @return
        bool Flushed()
        {
            return _flushed;
        }
    };
} // namespace base
#endif // HAS_THREAD
