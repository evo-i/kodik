cmake_minimum_required (VERSION 3.27)

string (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include (vcpkg)

project ("kodik" C)

option (USE_MIMALLOC
  "A compact general purpose allocator with excellent performance" ON)

find_package (Threads REQUIRED)
find_package (jansson CONFIG REQUIRED)
find_package (libuv CONFIG REQUIRED)

if (USE_MIMALLOC)
  find_package (mimalloc)
  if (NOT mimalloc_FOUND)
    find_package (mimalloc CONFIG REQUIRED)
  endif ()
endif ()

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_EXTENSIONS OFF)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory (src)
