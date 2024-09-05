#pragma once
#include <base/container/iterator/IEnumerator.h>
#include <base/container/iterator/IEnumeratorForwardIterator.h>
#include <base/container/iterator/IForwardIterator.h>
#include <memory>

namespace base
{
    /// @brief 可迭代容器接口。
    /// @tparam ItemType
    template <typename ItemType>
    class IEnumerable
    {
    private:
#pragma region ConstEnumerator

        template <typename ConstEnumeratorItemType>
        class ConstEnumerator :
            public IEnumerator<ConstEnumeratorItemType const>
        {
        private:
            std::shared_ptr<IEnumerator<ConstEnumeratorItemType>> _enumerator;

        public:
            ConstEnumerator(std::shared_ptr<IEnumerator<ConstEnumeratorItemType>> enumerator)
            {
                _enumerator = enumerator;
            }

            ConstEnumeratorItemType const &CurrentValue() override
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
        virtual std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() = 0;

        std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() const
        {
            return std::shared_ptr<IEnumerator<ItemType const>>{
                new ConstEnumerator<ItemType>{
                    const_cast<IEnumerable *>(this)->GetEnumerator(),
                },
            };
        }

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
    };
} // namespace base
