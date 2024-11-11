#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <base/string/ToHexString.h>
#include <format>
#include <iostream>

int main()
{
    base::ToHexStringOption option{
        .with_0x_prefix = false,
        .width = 4,
    };

    std::cout << base::ToHexString(static_cast<uint8_t>(66), option) << std::endl;
}
