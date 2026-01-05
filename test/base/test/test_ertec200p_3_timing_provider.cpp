#include "test_ertec200p_3_timing_provider.h" // IWYU pragma: keep
#include "base/embedded/sram/chip/ertec200p_3/ertec200p_3_timing_provider.h"
#include "base/string/define.h"

void base::test::test_ertec200p_3_timing_provider()
{
	std::cout << CODE_POS_STR;
	base::asynchronous_sram::chip::ertec200p_3::ertec200p_3_timing_provider provider{};
	base::asynchronous_sram::asynchronous_sram_timing timing = provider.GetTiming(base::unit::MHz{240});
	std::cout << timing << std::endl;
}
