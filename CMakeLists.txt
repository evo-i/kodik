cmake_minimum_required (VERSION 3.27)

project ("kodik" C)

find_package(PkgConfig REQUIRED)

include (CheckIncludeFile)
include (CheckSymbolExists)

option (USE_MIMALLOC
  "A compact general purpose allocator with excellent performance" ON)

find_package (Threads REQUIRED)
find_package (libuv REQUIRED)

pkg_check_modules (json REQUIRED IMPORTED_TARGET jansson)

check_include_file (stdio.h     HAVE_STDIO_H)
check_include_file (stdint.h    HAVE_STDINT_H)
check_include_file (inttypes.h  HAVE_INTTYPES_H)
check_include_file (threads.h   HAVE_THREADS_H)
check_include_file (pthread.h   HAVE_PTHREAD_H)
check_include_file (stdlib.h    HAVE_STDLIB_H)
check_include_file (string.h    HAVE_STRING_H)

check_symbol_exists (strdup string.h HAS_STRDUP)
check_symbol_exists (fopen stdio.h HAS_FOPEN)

if (USE_MIMALLOC)
  find_package (mimalloc REQUIRED)
endif ()

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_EXTENSIONS OFF)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory (src)
