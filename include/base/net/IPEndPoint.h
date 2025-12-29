#pragma once
#include "base/net/IEndPoint.h"
#include "base/net/IPAddress.h"

namespace base
{
	///
	/// @brief IP 终结点。
	///
	///
	class IPEndPoint :
		public base::IEndPoint
	{
	private:
		base::IPAddress _ip_address{};
		uint16_t _port = 0;

	public:
		///
		/// @brief 无参构造函数。构造出的终结点具有无效的 IP 地址，端口号为 0.
		///
		IPEndPoint() = default;

		///
		/// @brief 通过 IP 地址和端口号构造终结点。
		///
		/// @param ip
		/// @param port
		///
		IPEndPoint(base::IPAddress const &ip, uint16_t port)
		{
			_ip_address = ip;
			_port = port;
		}

		///
		/// @brief 此终结点所属的家族。
		///
		/// @return
		///
		virtual base::EndPointFamily Family() const override
		{
			if (_ip_address.Type() == base::IPAddressType::IPV4)
			{
				return base::EndPointFamily::IPV4;
			}
			else
			{
				return base::EndPointFamily::IPV6;
			}
		}

		base::IPAddress IPAddress() const
		{
			return _ip_address;
		}

		void SetIPAddress(base::IPAddress const &value)
		{
			_ip_address = value;
		}

		uint16_t Port() const
		{
			return _port;
		}

		void SetPort(uint16_t value)
		{
			_port = value;
		}

		///
		/// @brief 序列化为 json
		///
		/// @return
		///
		virtual base::Json ToJson() const override
		{
			return base::Json{
				{"ip", _ip_address.ToString()},
				{"port", _port},
			};
		}
	};

} // namespace base
