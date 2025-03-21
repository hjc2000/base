#pragma once
#include "base/container/iterator/IEnumerable.h"
#include <array>
#include <stdint.h>
#include <vector>

namespace base
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
		ModbusCrc16() = default;

		///
		/// @brief 自定义生成多项式。
		///
		/// @param polynomial
		///
		ModbusCrc16(uint16_t polynomial);

		///
		/// @brief 添加一个数进行计算。
		///
		/// @param data
		///
		void Add(uint8_t data);

		template <size_t length>
		void Add(std::array<uint8_t, length> const &datas)
		{
			for (uint8_t data : datas)
			{
				Add(data);
			}
		}

		void Add(std::vector<uint8_t> const &datas);
		void Add(base::IEnumerable<uint8_t> const &datas);

		///
		/// @brief 重置 CRC16 寄存器。
		///
		/// @warning 在开始新的一轮 CRC 校验前需要调用本方法重置 CRC16 寄存器，否则本轮添加的
		/// 数据会和上一轮的混在一起，继续往 CRC16 寄存器中叠加。
		///
		/// @note 如果每轮校验都重新构造一个新的本类对象，则无需调用本方法。
		///
		void ResetRegister();

		///
		/// @brief CRC16 寄存器的值。
		///
		/// @return uint16_t
		///
		uint16_t RegisterValue();

		///
		/// @brief CRC16 寄存器高字节。
		///
		/// @return uint8_t
		///
		uint8_t RegisterValueHighByte();

		///
		/// @brief CRC16 寄存器低字节。
		///
		/// @return uint8_t
		///
		uint8_t RegisterValueLowByte();
	};
} // namespace base
