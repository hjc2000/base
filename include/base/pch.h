#pragma once
///
/// * 本文件本身并不是预编译标头，但是可以被预编译标头包含。
///
/// * 这里的头文件都是较稳定的
///

// IWYU pragma: begin_keep
// IWYU pragma: begin_exports

#include "base/define.h"
#include "base/string/define.h"

#ifdef __cplusplus

	#include "base/bit/bit.h"
	#include "base/delegate/Delegate.h"
	#include "base/delegate/IEvent.h"
	#include "base/Guard.h"
	#include "base/IIdToken.h"
	#include "base/sfinae/Compare.h"
	#include "base/sfinae/Equal.h"
	#include "base/sfinae/explicitly_convertible_to.h"
	#include "base/sfinae/IsConst.h"
	#include "base/sfinae/TypeSelector.h"
	#include "base/stream/Stream.h"
	#include "base/task/delay.h"
	#include "base/task/IMutex.h"
	#include "base/task/Semaphore.h"
	#include "base/task/task.h"
	#include "base/time/DateTime.h"
	#include "base/time/DateTimeStringBuilder.h"
	#include "base/time/TimePointSinceEpoch.h"
	#include "base/unit/IUnit.h"
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
