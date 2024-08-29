#include "Initializer.h"
#include <base/Guard.h>

bool base::Initializer::_has_initialized = false;

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
    if (_has_initialized)
    {
        return;
    }

    _has_initialized = true;

    // 确保发生了异常也能将向量析构
    base::Guard g{[]()
                  {
                      InitFunctionVector().~vector();
                  }};

    for (auto &func : InitFunctionVector())
    {
        if (func)
        {
            func();
        }
    }
}
