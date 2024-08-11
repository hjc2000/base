#pragma once
#include <base/container/IEnumerator.h>
#include <base/container/IIterator.h>
#include <memory>

namespace base
{
    /// @brief 将 IEnumerator 包装为 C++ 迭代器
    /// @tparam ItemType
    template <typename ItemType>
    class IEnumeratorForwardIterator :
        public base::IForwardIterator<base::IEnumeratorForwardIterator<ItemType>, ItemType>
    {
    private:
        std::shared_ptr<IEnumerator<ItemType>> _enumertor;

    public:
        virtual ~IEnumeratorForwardIterator() = default;

        IEnumeratorForwardIterator(std::shared_ptr<IEnumerator<ItemType>> enumertor)
        {
            _enumertor = enumertor;
        }

        /// @brief 解引用
        /// @return
        ItemType &operator*() override
        {
            return _enumertor->CurrentValue();
        }

        /// @brief 前缀递增
        /// @return
        IEnumeratorForwardIterator<ItemType> &operator++() override
        {
            // 不做任何操作，因为 == 运算符里面已经 MoveNext 了。
            return *this;
        }

        bool operator==(IEnumeratorForwardIterator<ItemType> const &o) const override
        {
            /* C++ 范围 for 的机制是先判断不等于 end() 然后解引用。然后递增，进入下一循环。
             * IEnumerator 的操作顺序是先 MoveNext 然后判断是否成功，成功再利用 CurrentValue
             * 获取引用。
             *
             * 让 == 运算符返回 !_enumertor->MoveNext()，这样，范围 for 的判断不等于 end() 的
             * 步骤就会触发移动，并得到是否移动成功的结果，移动失败，就返回 true ，让范围 for 认为
             * 当前等于 end() ，于是结束迭代。
             */
            return !_enumertor->MoveNext();
        }
    };
} // namespace base
