#include "IDisposable.h"

base::ObjectDisposedException::ObjectDisposedException()
	: ObjectDisposedException("ObjectDisposedException")
{
}

base::ObjectDisposedException::ObjectDisposedException(std::string const &message)
	: std::runtime_error("ObjectDisposedException: " + message)
{
}
