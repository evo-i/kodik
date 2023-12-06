cmake_minimum_required (VERSION 3.27)

project ("kodik" C)

find_package(PkgConfig REQUIRED)

option (USE_MIMALLOC
  "A compact general purpose allocator with excellent performance" ON)

pkg_check_modules (json REQUIRED IMPORTED_TARGET jansson)

find_package (Threads REQUIRED)
find_package (libuv REQUIRED)

if (USE_MIMALLOC)
  find_package (mimalloc REQUIRED)
endif ()

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_EXTENSIONS OFF)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory (src)
