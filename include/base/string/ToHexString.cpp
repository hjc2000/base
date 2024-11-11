#include "ToHexString.h"
#include <iomanip>

std::string base::ToHexString(int8_t number, ToHexStringOption const &option)
{
    return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(uint8_t number, ToHexStringOption const &option)
{
    return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(int16_t number, ToHexStringOption const &option)
{
    return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(uint16_t number, ToHexStringOption const &option)
{
    return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(int32_t number, ToHexStringOption const &option)
{
    return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(uint32_t number, ToHexStringOption const &option)
{
    return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(int64_t number, ToHexStringOption const &option)
{
    return ToHexString(static_cast<uint64_t>(number), option);
}

std::string base::ToHexString(uint64_t number, ToHexStringOption const &option)
{
    std::stringstream string_stream;
    if (option.with_0x_prefix)
    {
        string_stream << "0x";
    }

    if (option.width > 0)
    {
        string_stream << std::setw(option.width) << std::setfill('0');
    }

    string_stream << std::hex << number;
    return string_stream.str();
}

std::string base::ToHexString(uint8_t *buffer, int32_t size, ToHexStringOption const &option)
{
    if (size <= 0)
    {
        return "";
    }

    std::stringstream string_stream;
    for (int i = 0; i < size; i++)
    {
        string_stream << base::ToHexString(buffer[i], option) << ", ";
        if ((i + 1) % 20 == 0)
        {
            string_stream << '\n';
        }
    }

    string_stream << '\n';
    return string_stream.str();
}
