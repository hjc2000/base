# 编译目标
add_library(${ProjectName} STATIC)
target_import_src(${ProjectName})

target_import_boost(${ProjectName} PUBLIC)
target_import_nlohmann_json(${ProjectName} PUBLIC)

if(has_thread)
	message(STATUS "此平台拥有线程")
	target_compile_definitions(${ProjectName} PUBLIC HAS_THREAD=1)
else()
	message(STATUS "此平台没有线程")
	target_compile_definitions(${ProjectName} PUBLIC HAS_THREAD=0)
endif()

# 添加测试程序
if(("${platform}" STREQUAL "msys") OR
   ("${platform}" STREQUAL "msys-clang"))
	set(exe_name "base-test")
	add_executable(${exe_name} ${CMAKE_CURRENT_SOURCE_DIR}/exe/main.cpp)
	target_link_libraries(${exe_name} ${ProjectName})
	target_install(${exe_name})
	target_total_install(${exe_name})
endif()
