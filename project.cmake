# 编译目标
add_library(${ProjectName})
target_import_src(${ProjectName})
target_install_obj_dir(${ProjectName})

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
if(platform STREQUAL "msys")
	set(exe_name "test")
	add_executable(${exe_name} ${CMAKE_CURRENT_SOURCE_DIR}/exe/main.cpp)

	target_link_libraries(${ProjectName} PUBLIC -Wl,--start-group)
	target_link_libraries(${exe_name} ${ProjectName})
	target_link_libraries(${ProjectName} PUBLIC -Wl,--end-group)

	target_install(${exe_name})
endif()
