#include "Console.h" // IWYU pragma: keep
#include "base/SingletonProvider.h"

namespace
{
	base::SingletonProvider<base::Console> _console_instance_provider;

} // namespace

base::Console &base::console()
{
	return _console_instance_provider.Instance();
}
