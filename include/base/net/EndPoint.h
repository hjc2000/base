#pragma once

namespace base
{
    /// @brief 终结点家族枚举
    enum class EndPointFamily
    {
        AF_UNIX = 1,
        IPV4 = 2,
        AF_IMPLINK = 3,
        AF_PUP = 4,
        AF_CHAOS = 5,
        AF_NS = 6,
        AF_IPX = AF_NS,
        AF_ISO = 7,
        AF_OSI = AF_ISO,
        AF_ECMA = 8,
        AF_DATAKIT = 9,
        AF_CCITT = 10,
        AF_SNA = 11,
        AF_DECnet = 12,
        AF_DLI = 13,
        AF_LAT = 14,
        AF_HYLINK = 15,
        AF_APPLETALK = 16,
        AF_NETBIOS = 17,
        AF_VOICEVIEW = 18,
        AF_FIREFOX = 19,
        AF_UNKNOWN1 = 20,
        AF_BAN = 21,
        AF_ATM = 22,
        IPV6 = 23,
        AF_CLUSTER = 24,
        AF_12844 = 25,
        AF_IRDA = 26,
        AF_NETDES = 28,
        AF_TCNPROCESS = 29,
        AF_TCNMESSAGE = 30,
        AF_ICLFXBM = 31,
        AF_BTH = 32,
    };

    /// @brief 终结点
    class EndPoint
    {
    public:
        virtual EndPointFamily Family() const = 0;
    };
} // namespace base
