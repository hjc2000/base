#pragma once
#include <base/string/ICanToString.h>

namespace base
{
    /// @brief 终结点家族枚举
    enum class EndPointFamily
    {
        UNIX = 1,
        IPV4 = 2,
        IMPLINK = 3,
        PUP = 4,
        CHAOS = 5,
        NS = 6,
        IPX = EndPointFamily::NS,
        ISO = 7,
        OSI = EndPointFamily::ISO,
        ECMA = 8,
        DATAKIT = 9,
        CCITT = 10,
        SNA = 11,
        DECnet = 12,
        DLI = 13,
        LAT = 14,
        HYLINK = 15,
        APPLETALK = 16,
        NETBIOS = 17,
        VOICEVIEW = 18,
        FIREFOX = 19,
        UNKNOWN1 = 20,
        BAN = 21,
        ATM = 22,
        IPV6 = 23,
        CLUSTER = 24,
        AF12844 = 25,
        IRDA = 26,
        NETDES = 28,
        TCNPROCESS = 29,
        TCNMESSAGE = 30,
        ICLFXBM = 31,
        BTH = 32,
    };

    /// @brief 终结点
    class EndPoint :
        public base::ICanToString
    {
    public:
        virtual base::EndPointFamily Family() const = 0;

        /// @brief 转化为字符串
        /// @return
        virtual std::string ToString() const = 0;
    };
} // namespace base
