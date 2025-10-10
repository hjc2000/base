#pragma once

namespace base::profidrive
{
	///
	/// @brief 错误类。
	///
	///
	enum class FaultClass
	{
		///
		/// @brief 微控制器软件或硬件错误。
		///
		///
		MicrocontrollerHardwareOrSoftware = 1,

		///
		/// @brief 主供电错误。
		///
		/// @note 例如缺相、过压、欠压。
		///
		/// @note 这应该指的是交流电源的错误。
		///
		MainSupply = 2,

		///
		/// @brief 低压供电错误。
		///
		/// @note 例如 24V 供电发生异常。
		///
		LowVoltageSupply = 3,

		///
		/// @brief 直流环节过电压。
		///
		/// @note 例如回馈制动导致的整流桥输出端电容的过电压。
		///
		DC_Link_Overvoltage = 4,

		///
		/// @brief 电力电子错误。
		///
		/// @note 例如逆变器错误。
		///
		PowerElectronics = 5,

		///
		/// @brief 电力设备过热。
		///
		///
		ElectronicDeviceOvertemperature = 6,

		///
		/// @brief 隔离错误。
		///
		/// @note 相间短路或对地短路。
		///
		Isolation = 7,

		///
		/// @brief 电机过载。
		///
		///
		MotorOverload = 8,

		///
		/// @brief 现场总线系统错误。
		///
		FieldbusSystem = 9,

		///
		/// @brief 安全通道错误。
		///
		SafetyChannel = 10,

		///
		/// @brief 反馈错误。
		///
		/// @note 例如编码器错误。
		///
		Feedback = 11,

		///
		/// @brief 内部通信错误。
		///
		/// @note 如果伺服的控制板由主板和通信板组成，这可能有这个类别的错误。
		///
		InternalCommunication = 12,

		///
		/// @brief 整流错误。
		///
		/// @note 内部整流桥错误。
		///
		Infeed = 13,

		///
		/// @brief 刹车电阻错误。
		///
		/// @note 例如刹车电阻过热，刹车电阻开路。
		///
		BrakeResistor = 14,

		///
		/// @brief 整流桥前面的线性滤波器错误。
		///
		LineFilter = 15,

		///
		/// @brief 外部引入的错误。
		///
		/// @note 错误来自外部，不来自驱动器本身。例如用户外接了一个温度传感器，温度传感器发生错误。
		///
		External = 16,

		///
		/// @brief 技术错误。
		///
		/// @note 驱动器内部的数据监视器发现了错误。例如检测到转矩超出设定的限制值。
		///
		Technology = 17,

		///
		/// @brief 工程错误。
		///
		/// @note 组态工程错误。
		///
		Engineering = 18,

		///
		/// @brief 其他错误。
		///
		///
		Other = 19,

		///
		/// @brief 辅助设备错误。
		///
		/// @note 例如大型驱动器的辅助散热器发生错误。
		///
		AuxiliaryDevice = 20,
	};

} // namespace base::profidrive
