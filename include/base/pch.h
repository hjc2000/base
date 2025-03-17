#pragma once
// IWYU pragma: begin_keep
// IWYU pragma: begin_exports

#include <base/define.h>
#include <base/string/define.h>

#ifdef __cplusplus
	#include <algorithm>
	#include <array>
	#include <atomic>
	#include <base/container/Array.h>
	#include <base/container/ArraySpan.h>
	#include <base/container/Dictionary.h>
	#include <base/container/IDictionary.h>
	#include <base/container/IList.h>
	#include <base/container/IRawArray.h>
	#include <base/container/iterator/IEnumerable.h>
	#include <base/container/iterator/IEnumerator.h>
	#include <base/container/List.h>
	#include <base/Guard.h>
	#include <base/IDisposable.h>
	#include <base/LockGuard.h>
	#include <base/sfinae/Compare.h>
	#include <base/sfinae/Equal.h>
	#include <base/sfinae/IsConst.h>
	#include <base/sfinae/TypeSelector.h>
	#include <base/stream/ReadOnlySpan.h>
	#include <base/stream/Span.h>
	#include <base/string/ICanToString.h>
	#include <base/string/Json.h>
	#include <bit>
	#include <boost/multiprecision/cpp_int.hpp>
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
	#include <vector>

	#if HAS_THREAD
		#include <iostream>
		#include <mutex>
		#include <semaphore>
	#endif
#endif

// IWYU pragma: end_exports
// IWYU pragma: end_keep
