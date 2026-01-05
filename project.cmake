# 编译目标
add_library(${ProjectName} STATIC)
target_compile_definitions(${ProjectName} PUBLIC __test_resource_pasth="${CMAKE_CURRENT_SOURCE_DIR}/test-resource")
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
	set(test_exe_target_name "base-test")
	add_executable(${test_exe_target_name})
	target_import_test(${test_exe_target_name})

	target_link_libraries(${test_exe_target_name} PUBLIC ${ProjectName})
endif()
