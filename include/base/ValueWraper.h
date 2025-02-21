#pragma once

namespace base
{
	template <typename ValueType>
	class ValueWraper
	{
	private:
		ValueType _value{};

	public:
		explicit ValueWraper(ValueType const &value)
			: _value(value)
		{
		}

		ValueType const &Value() const
		{
			return _value;
		}
	};
} // namespace base
