#pragma once
#include <base/container/iterator/IEnumerator.h>
#include <base/container/iterator/IEnumeratorForwardIterator.h>
#include <base/container/iterator/IForwardIterator.h>
#include <memory>

namespace base
{
    /// @brief C# 风格的可迭代容器接口。
    /// @tparam ItemType
    template <typename ItemType>
    class IEnumerable
    {
    private:
#pragma region ConstEnumerator

        /// @brief const 迭代器
        /// @tparam ConstEnumerator_ItemType
        template <typename ConstEnumerator_ItemType>
        class ConstEnumerator :
            public IEnumerator<ConstEnumerator_ItemType const>
        {
        private:
            std::shared_ptr<IEnumerator<ConstEnumerator_ItemType>> _enumerator;

        public:
            ConstEnumerator(std::shared_ptr<IEnumerator<ConstEnumerator_ItemType>> enumerator)
            {
                _enumerator = enumerator;
            }

            ConstEnumerator_ItemType const &CurrentValue() override
            {
                return _enumerator->CurrentValue();
            }

            virtual bool MoveNext() override
            {
                return _enumerator->MoveNext();
            }

            virtual void Reset() override
            {
                _enumerator->Reset();
            }
        };

#pragma endregion

    public:
        /// @brief 获取非 const 迭代器
        /// @return
        virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;

        /// @brief 获取 const 迭代器
        /// @return
        std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() const
        {
            return std::shared_ptr<IEnumerator<ItemType const>>{
                new ConstEnumerator<ItemType>{
                    const_cast<IEnumerable *>(this)->GetEnumerator(),
                },
            };
        }

#pragma region C++风格的可迭代容器实现

        IEnumeratorForwardIterator<ItemType> begin()
        {
            return IEnumeratorForwardIterator<ItemType>{GetEnumerator()};
        }

        IEnumeratorForwardIterator<ItemType> end()
        {
            return IEnumeratorForwardIterator<ItemType>{GetEnumerator()};
        }

        IEnumeratorForwardIterator<ItemType const> begin() const
        {
            return IEnumeratorForwardIterator<ItemType const>{GetEnumerator()};
        }

        IEnumeratorForwardIterator<ItemType const> end() const
        {
            return IEnumeratorForwardIterator<ItemType const>{GetEnumerator()};
        }

#pragma endregion
    };
} // namespace base
