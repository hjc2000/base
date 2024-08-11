#include "Initializer.h"

std::vector<std::function<void()>> &base::Initializer::InitFunctionVector()
{
    static std::vector<std::function<void()>> vec;
    return vec;
}

base::Initializer::Initializer(std::function<void()> init_func)
{
    InitFunctionVector().push_back(init_func);
}

void base::Initializer::Initialize()
{
    for (auto &func : InitFunctionVector())
    {
        try
        {
            if (func)
            {
                func();
            }
        }
        catch (...)
        {
        }
    }

    InitFunctionVector().~vector();
}
