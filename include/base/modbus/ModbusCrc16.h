#pragma once
#include "base/bit/bit.h"
#include "base/container/iterator/IEnumerable.h"
#include "base/stream/ReadOnlySpan.h"
#include <array>
#include <stdint.h>
#include <vector>

namespace base::modbus
{
	///
	/// @brief modbus CRC16 校验器。
	///
	///
	class ModbusCrc16 final
	{
	private:
		uint16_t _crc16_register = UINT16_MAX;

		///
		/// @brief 默认的生成多项式是：
		/// 	x16+x15+x2+1
		/// 这个生成多项式转化成系数，从最低次的系数开始写，最低次是 x^0，系数是 1，
		/// 写在最左边，然后 x^1 的系数是 0，接着写在右边，x^2 的系数是 1，接着写在
		/// 右边，以此类推，得到：
		/// 	10100000000000011
		/// x^16 的系数是 1，但是最高次的系数是要被忽略的，因为最高次的系数一定是 1，
		/// 例如这里的最高次是 16 次，如果 16 次的系数不是 1，那最高次就变成 15 次
		/// 而不是 16 次了。
		///
		/// 忽略最高次的系数后，得到
		/// 	1010000000000001
		/// 这个数称为生成数。
		///
		/// 这个生成数和生成多项式是反着来的，最高位对应的是生成多项式最低次的系数。
		/// 转化为 16 进制就是 0xA001。
		///
		uint16_t _polynomial = 0xA001;

	public:
		///
		/// @brief 生成多项式使用 0xA001。
		///
		///
		constexpr ModbusCrc16() = default;

		///
		/// @brief 自定义生成多项式。
		///
		/// @param polynomial
		///
		constexpr ModbusCrc16(uint16_t polynomial)
			: _polynomial(polynomial)
		{
		}

		///
		/// @brief 添加一个数进行计算。
		///
		/// @param data
		///
		constexpr void Add(uint8_t data)
		{
			_crc16_register ^= static_cast<uint16_t>(data);
			for (int i = 0; i < 8; i++)
			{
				bool lsb = base::bit::ReadBit(_crc16_register, 0);
				_crc16_register >>= 1;
				if (lsb)
				{
					_crc16_register ^= _polynomial;
				}
			}
		}

		void Add(base::ReadOnlySpan const &span)
		{
			for (int32_t i = 0; i < span.Size(); i++)
			{
				Add(span[i]);
			}
		}

		template <size_t length>
		constexpr void Add(std::array<uint8_t, length> const &datas)
		{
			for (uint8_t data : datas)
			{
				Add(data);
			}
		}

		void Add(std::vector<uint8_t> const &datas)
		{
			for (uint8_t data : datas)
			{
				Add(data);
			}
		}

		void Add(base::IEnumerable<uint8_t> const &datas)
		{
			for (uint8_t data : datas)
			{
				Add(data);
			}
		}

		///
		/// @brief 重置 CRC16 寄存器。
		///
		/// @warning 在开始新的一轮 CRC 校验前需要调用本方法重置 CRC16 寄存器，否则本轮添加的
		/// 数据会和上一轮的混在一起，继续往 CRC16 寄存器中叠加。
		///
		/// @note 如果每轮校验都重新构造一个新的本类对象，则无需调用本方法。
		///
		constexpr void ResetRegister()
		{
			_crc16_register = UINT16_MAX;
		}

		///
		/// @brief CRC16 寄存器的值。
		///
		/// @return uint16_t
		///
		constexpr uint16_t RegisterValue()
		{
			return _crc16_register;
		}

		///
		/// @brief CRC16 寄存器高字节。
		///
		/// @return uint8_t
		///
		constexpr uint8_t RegisterValueHighByte()
		{
			return static_cast<uint8_t>(_crc16_register >> 8);
		}

		///
		/// @brief CRC16 寄存器低字节。
		///
		/// @return uint8_t
		///
		constexpr uint8_t RegisterValueLowByte()
		{
			return static_cast<uint8_t>(_crc16_register);
		}
	};

} // namespace base::modbus
