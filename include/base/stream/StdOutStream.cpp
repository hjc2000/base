#include "StdOutStream.h" // IWYU pragma: keep
#include "base/SingletonProvider.h"

namespace
{
	class Initializer
	{
	public:
		std::shared_ptr<base::Stream> _std_ouot_stream{new base::StdOutStream{}};
	};

	base::SingletonProvider<Initializer> _initializer_provider{};

} // namespace

std::shared_ptr<base::Stream> base::std_out_stream()
{
	return _initializer_provider.Instance()._std_ouot_stream;
}
