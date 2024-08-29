cmake_minimum_required(VERSION 3.8)
include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)
include(target_import_boost)
include(target_import_nlohmann_json)

set(ProjectName base)
project(${ProjectName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

# 编译目标
add_library(${ProjectName})
target_import_src(${ProjectName})
target_import_boost(${ProjectName} PUBLIC)
target_import_nlohmann_json(${ProjectName} PUBLIC)

if(has_thread)
	message(STATUS "此平台拥有线程")
	target_compile_definitions(${ProjectName} PUBLIC HAS_THREAD=1)
else()
	message(STATUS "此平台没有线程")
endif()

set(CMAKE_INSTALL_PREFIX $ENV{cpp_lib_build_scripts_path}/${platform}/.libs/${ProjectName}/)
