#pragma once
#ifndef HAS_THREAD
#define HAS_THREAD 0
#endif

#include <base/container/IEnumerable.h>
#include <vector>

namespace base
{
	template <typename ItemType>
	class VectorEnumerable
		: public IEnumerable<ItemType>
	{
	private:
		std::vector<ItemType> &_vector;

		template <typename EnumeratorItemType>
		class VectorEnumerator
			: public base::IEnumerator<EnumeratorItemType>
		{
		private:
			std::vector<EnumeratorItemType> &_vector;
			size_t _index = 0;
			bool _is_first_move = true;

		public:
			VectorEnumerator(std::vector<EnumeratorItemType> &vector)
				: _vector(vector)
			{
			}

			EnumeratorItemType &CurrentValue() override
			{
				return _vector[_index];
			}

			bool MoveNext() override
			{
				if (_is_first_move)
				{
					_is_first_move = false;
				}
				else
				{
					_index++;
				}

				if (_index >= _vector.size())
				{
					return false;
				}

				return true;
			}

			void Reset() override
			{
				_index = 0;
			}
		};

		template <typename EnumeratorItemType>
		class ConstVectorEnumerator
			: public base::IEnumerator<EnumeratorItemType const>
		{
		private:
			std::vector<EnumeratorItemType> const &_vector;
			size_t _index = 0;
			bool _is_first_move = true;

		public:
			ConstVectorEnumerator(std::vector<EnumeratorItemType> const &vector)
				: _vector(vector)
			{
			}

			EnumeratorItemType const &CurrentValue() override
			{
				return _vector[_index];
			}

			bool MoveNext() override
			{
				if (_is_first_move)
				{
					_is_first_move = false;
				}
				else
				{
					_index++;
				}

				if (_index >= _vector.size())
				{
					return false;
				}

				return true;
			}

			void Reset() override
			{
				_index = 0;
			}
		};

	public:
		VectorEnumerable(std::vector<ItemType> &vector)
			: _vector(vector)
		{
		}

		std::shared_ptr<IEnumerator<ItemType>> GetEnumerator() override
		{
			return std::shared_ptr<IEnumerator<ItemType>>{new VectorEnumerator<ItemType>{_vector}};
		}

		std::shared_ptr<IEnumerator<ItemType const>> GetEnumerator() const override
		{
			return std::shared_ptr<IEnumerator<ItemType const>>{new ConstVectorEnumerator<ItemType>{_vector}};
		}
	};

#if HAS_THREAD
	void TestVectorEnumerable();
#endif
}
