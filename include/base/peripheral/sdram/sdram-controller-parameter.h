#pragma once

namespace base
{
	namespace sdram
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
			explicit BankCount(int value)
				: _value(value)
			{
			}

			int Value() const
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
			explicit RowBitCount(int value)
				: _value(value)
			{
			}

			int Value() const
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
			explicit ColumnBitCount(int value)
				: _value(value)
			{
			}

			int Value() const
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
			explicit DataWidth(int value)
				: _value(value)
			{
			}

			int Value() const
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
			explicit ReadBurstLength(int value)
				: _value(value)
			{
			}

			int Value() const
			{
				return _value;
			}
		};

	} // namespace sdram
} // namespace base
