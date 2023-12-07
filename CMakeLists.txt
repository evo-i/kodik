cmake_minimum_required (VERSION 3.27)

project ("kodik" C)

find_package(PkgConfig REQUIRED)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include (CheckIncludeFile)
include (CheckSymbolExists)

option (KODIK_TESTING "Testing..." ON)
option (KODIK_USE_MIMALLOC "mimalloc library" ON)

find_package (Threads REQUIRED)

pkg_check_modules (json REQUIRED IMPORTED_TARGET jansson)

check_include_file (stdio.h     HAVE_STDIO_H)
check_include_file (stdint.h    HAVE_STDINT_H)
check_include_file (inttypes.h  HAVE_INTTYPES_H)
check_include_file (stdlib.h    HAVE_STDLIB_H)
check_include_file (string.h    HAVE_STRING_H)

check_include_file (threads.h   HAVE_THREADS_H)
check_include_file (pthread.h   HAVE_PTHREAD_H)

check_symbol_exists (strdup string.h HAS_STRDUP)
check_symbol_exists (fopen stdio.h HAS_FOPEN)

if (USE_MIMALLOC)
  find_package (mimalloc REQUIRED)
endif ()

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_EXTENSIONS OFF)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory (src)

if (KODIK_TESTING)
  enable_testing()
  add_subdirectory (vendor/munit EXCLUDE_FROM_ALL)
  add_subdirectory (tests)
endif ()
