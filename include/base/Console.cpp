#include "Console.h" // IWYU pragma: keep
#include <cstdint>

#if HAS_THREAD

base::Console &base::console()
{
	static base::Console instance{};
	return instance;
}

#else

namespace
{
	struct
	{
		bool _initialized = false;
		alignas(base::Console) uint8_t _console_obj_buffer[sizeof(base::Console)];
	} _console_obj_provider;

} // namespace

base::Console &base::console()
{
	if (!_console_obj_provider._initialized)
	{
		new (_console_obj_provider._console_obj_buffer) base::Console{};
	}

	return *reinterpret_cast<base::Console *>(_console_obj_provider._console_obj_buffer);
}

#endif // HAS_THREAD
