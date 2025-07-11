#pragma once
#include <string>

namespace base
{
	namespace serial
	{
		class SerialPortInfomation
		{
		private:
			std::string _name{};
			std::string _description{};

		public:
			constexpr SerialPortInfomation(std::string const &name,
										   std::string const &description)
			{
				_name = name;
				_description = description;
			}

			///
			/// @brief 串口名称。
			///
			/// @return
			///
			constexpr std::string const &Name() const
			{
				return _name;
			}

			///
			/// @brief 串口描述。
			///
			/// @return
			///
			constexpr std::string const &Description() const
			{
				return _description;
			}
		};

	} // namespace serial
} // namespace base
