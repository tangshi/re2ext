project(re2_ext)
cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)

pkg_search_module(re2 REQUIRED re2)

add_executable(${PROJECT_NAME} demo.cpp matchobject.h matchobject.cc re2_ext.h re2_ext.cc utf.h rune.cc)

target_link_libraries(${PROJECT_NAME} ${re2_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${re2_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${re2_CFLAGS_OTHER})
