#include "Wrapper.h"
#include <memory>

using namespace base;

class IntWrapper final
	: public Wrapper<int>
{
private:
	int *_num = new int{0};

public:
	~IntWrapper()
	{
		delete _num;
	}

	int *&WrappedObj() override
	{
		return _num;
	}

	int *WrappedObj() const override
	{
		return _num;
	}
};

Wrapper<int> &CreateIntWrapper()
{
	static IntWrapper o;
	return o;
}
