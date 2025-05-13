#pragma once
// IWYU pragma: begin_keep
// IWYU pragma: begin_exports

#include "base/define.h"

#ifdef __cplusplus

	#include "boost/multiprecision/cpp_int.hpp"
	#include "nlohmann/json.hpp"
	#include <algorithm>
	#include <array>
	#include <atomic>
	#include <bit>
	#include <chrono>
	#include <cmath>
	#include <cstddef>
	#include <cstdint>
	#include <cstdlib>
	#include <functional>
	#include <initializer_list>
	#include <map>
	#include <memory>
	#include <set>
	#include <stdexcept>
	#include <string>
	#include <type_traits>
	#include <vector>

	#if HAS_THREAD

		#include <filesystem>
		#include <format>
		#include <fstream>
		#include <iostream>
		#include <mutex>
		#include <semaphore>
		#include <sstream>
		#include <thread>

	#endif
#endif

// IWYU pragma: end_exports
// IWYU pragma: end_keep
