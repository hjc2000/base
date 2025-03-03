#pragma once
#include <base/net/IEndPoint.h>
#include <base/net/IPAddress.h>

namespace base
{
	/**
	 * @brief IP 终结点。
	 *
	 */
	class IPEndPoint :
		public base::IEndPoint
	{
	private:
		base::IPAddress _ip_address{};
		uint16_t _port = 0;

	public:
		/**
		 * @brief 无参构造函数。构造出的终结点具有无效的 IP 地址，端口号为 0.
		 *
		 */
		IPEndPoint() = default;

		/**
		 * @brief 通过 IP 地址和端口号构造终结点。
		 *
		 * @param ip
		 * @param port
		 */
		IPEndPoint(base::IPAddress const &ip, uint16_t port);

	public:
		/**
		 * @brief 此终结点所属的家族。
		 *
		 * @return base::EndPointFamily
		 */
		virtual base::EndPointFamily Family() const override;

		base::IPAddress IPAddress() const;
		void SetIPAddress(base::IPAddress const &value);

		uint16_t Port() const;
		void SetPort(uint16_t value);

		/**
		 * @brief 序列化为 json
		 *
		 * @return Json
		 */
		virtual Json ToJson() const override;
	};
} // namespace base
