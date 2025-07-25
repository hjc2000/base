#include "envirenment.h"
#include "base/string/KeyValueString.h"
#include "string/String.h"
#include <cstdlib>
#include <mutex>

#if HAS_THREAD

namespace
{
	std::mutex _lock;

	char **EnvirenmentVariableBuffer()
	{
		return environ;
	}

} // namespace

std::string base::GetEnvirenmentVariable(std::string const &name)
{
	std::lock_guard l{_lock};
	return std::getenv(name.c_str());
}

std::vector<base::KeyValueString> base::GetEnvirenmentVariableVector()
{
	std::lock_guard l{_lock};
	std::vector<base::KeyValueString> ret;
	for (char **begin = EnvirenmentVariableBuffer(); *begin != nullptr; begin++)
	{
		char const *str = *begin;
		ret.push_back(base::KeyValueString{str});
	}

	return ret;
}

base::Dictionary<base::String, base::String> base::GetEnvirenmentVariableDictionary()
{
	std::lock_guard l{_lock};
	base::Dictionary<base::String, base::String> ret;
	for (char **begin = EnvirenmentVariableBuffer(); *begin != nullptr; begin++)
	{
		base::KeyValueString key_value{*begin};
		ret.Add(key_value.Key(), key_value.Value());
	}

	return ret;
}

#endif // HAS_THREAD
