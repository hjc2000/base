#include "BinarySemaphore.h" // IWYU pragma: keep

base::task::BinarySemaphore::BinarySemaphore(bool initial_release)
	: _handle(base::task::create_binary_semaphore(initial_release))
{
}
