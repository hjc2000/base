#pragma once

namespace base::sdram
{
	///
	/// @brief SDRAM 中 BANK 的数量。
	///
	///
	class BankCount
	{
	private:
		int _value = 0;

	public:
		constexpr explicit BankCount(int value)
			: _value(value)
		{
		}

		constexpr int Value() const
		{
			return _value;
		}
	};

	///
	/// @brief 行地址的位数。
	///
	///
	class RowBitCount
	{
	private:
		int _value = 0;

	public:
		constexpr explicit RowBitCount(int value)
			: _value(value)
		{
		}

		constexpr int Value() const
		{
			return _value;
		}
	};

	///
	/// @brief 列地址的位数。
	///
	///
	class ColumnBitCount
	{
	private:
		int _value = 0;

	public:
		constexpr explicit ColumnBitCount(int value)
			: _value(value)
		{
		}

		constexpr int Value() const
		{
			return _value;
		}
	};

	///
	/// @brief 数据宽度，或者说数据总线位数。
	///
	///
	class DataWidth
	{
	private:
		int _value = 0;

	public:
		constexpr explicit DataWidth(int value)
			: _value(value)
		{
		}

		constexpr int Value() const
		{
			return _value;
		}
	};

	///
	/// @brief 读突发长度。
	///
	///
	class ReadBurstLength
	{
	private:
		int _value = 0;

	public:
		constexpr explicit ReadBurstLength(int value)
			: _value(value)
		{
		}

		constexpr int Value() const
		{
			return _value;
		}
	};

} // namespace base::sdram
