cmake_minimum_required(VERSION 2.8)

find_package(PkgConfig REQUIRED)

pkg_search_module(re2 REQUIRED re2)

file(GLOB_RECURSE re2ext_HEADERS re2ext.h matchobject.h)
file(GLOB_RECURSE re2ext_SRCS re2ext.cc matchobject.cc rune.cc)

add_library(re2ext SHARED ${re2ext_HEADERS} ${re2ext_SRCS})

target_link_libraries(re2ext ${re2_LIBRARIES})
target_include_directories(re2ext PUBLIC ${re2_INCLUDE_DIRS})
target_compile_options(re2ext PUBLIC ${re2_CFLAGS_OTHER})
