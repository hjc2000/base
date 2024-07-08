#pragma once
#include <algorithm>
#include <base/container/IList.h>
#include <stdexcept>
#include <vector>

namespace base
{
	template <typename T>
	class List : public base::IList<T>
	{
	private:
		std::vector<T> _vector;

	public:
		List() = default;
		List(List<T> const &o);
		List(std::vector<T> const &o);
		List<T> &operator=(List<T> const &value);
		List<T> &operator=(std::vector<T> const &value);

		void Add(T const &item) override;
		using IList<T>::Add;

		void Insert(int const index, T const &item) override;
		bool Remove(T const &item) override;
		void RemoveAt(int const index) override;
		int IndexOf(T const &item) const override;
		bool Contains(T const &item) const override;
		void Clear() override;
		int Count() const override;

		T &operator[](int const index) override;
		T const &operator[](int const index) const override;

		/// <summary>
		///		将本列表内的元素拷贝到向量中。
		/// </summary>
		/// <returns></returns>
		std::vector<T> ToVector();

		/// <summary>
		///		转发到 std::vector 的相等判断逻辑。
		/// </summary>
		/// <param name="another"></param>
		/// <returns></returns>
		bool operator==(List<T> const &another) const;
	};

#pragma region 实现
	template <typename T>
	inline List<T>::List(List<T> const &another)
	{
		_vector = another._vector;
	}

	template <typename T>
	inline List<T>::List(std::vector<T> const &o)
	{
		_vector = o;
	}

	template <typename T>
	inline List<T> &List<T>::operator=(List<T> const &value)
	{
		_vector = value._vector;
		return *this;
	}

	template <typename T>
	inline List<T> &List<T>::operator=(std::vector<T> const &value)
	{
		_vector = value;
		return *this;
	}

	template <typename T>
	inline void List<T>::Add(T const &item)
	{
		_vector.push_back(item);
	}

	template <typename T>
	inline void List<T>::Insert(int const index, T const &item)
	{
		if (index < 0 || index > int(_vector.size()))
		{
			throw std::out_of_range{"索引超出范围"};
		}

		_vector.insert(_vector.begin() + index, item);
	}

	template <typename T>
	inline bool List<T>::Remove(T const &item)
	{
		auto it = std::find(_vector.begin(), _vector.end(), item);
		if (it != _vector.end())
		{
			_vector.erase(it);
			return true; // 返回 true 表示成功找到并删除了元素
		}

		return false; // 如果没有找到元素，返回 false
	}

	template <typename T>
	inline void List<T>::RemoveAt(int const index)
	{
		if (index < 0 || index >= (int)_vector.size())
		{
			throw std::out_of_range{"索引超出范围"};
		}

		_vector.erase(_vector.begin() + index);
	}

	template <typename T>
	inline int List<T>::IndexOf(T const &item) const
	{
		auto it = std::find(_vector.begin(), _vector.end(), item);
		if (it != _vector.end())
		{
			return (int)std::distance(_vector.begin(), it); // 返回元素的索引
		}

		return -1; // 如果没有找到元素，返回 -1
	}

	template <typename T>
	inline bool List<T>::Contains(T const &item) const
	{
		return std::find(_vector.begin(), _vector.end(), item) != _vector.end();
	}

	template <typename T>
	inline void List<T>::Clear()
	{
		_vector.clear();
	}

	template <typename T>
	inline int List<T>::Count() const
	{
		return (int)_vector.size();
	}

	template <typename T>
	inline T &List<T>::operator[](int const index)
	{
		if (index < 0 || index >= int(_vector.size()))
		{
			throw std::out_of_range{"索引超出范围"};
		}

		return _vector[index];
	}

	template <typename T>
	inline T const &List<T>::operator[](int const index) const
	{
		if (index < 0 || index >= int(_vector.size()))
		{
			throw std::out_of_range{"索引超出范围"};
		}

		return _vector[index];
	}

	template <typename T>
	inline std::vector<T> List<T>::ToVector()
	{
		return _vector;
	}

	template <typename T>
	inline bool List<T>::operator==(List<T> const &another) const
	{
		return _vector == another._vector;
	}
#pragma endregion
}
