#include "IBinarySemaphore.h"
#include "BinarySemaphore.h"
#include <memory>

#if HAS_THREAD

std::shared_ptr<base::IBinarySemaphore> base::CreateIBinarySemaphore(bool initial_release)
{
	return std::shared_ptr<base::BinarySemaphore>{new base::BinarySemaphore{initial_release}};
}

#endif // HAS_THREAD
