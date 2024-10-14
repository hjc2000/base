#include <array>
#include <base/bit/BitConverter.h>
#include <base/container/Array.h>
#include <base/container/Dictionary.h>
#include <base/container/List.h>
#include <format>
#include <iostream>

int main()
{
    uint16_t num = 666;
    std::array<uint8_t, sizeof(num)> bytes = base::BitConverter::GetBytes(num);
    num = base::BitConverter::ToUInt16(bytes.data(), 0);
    std::cout << num << std::endl;
}
