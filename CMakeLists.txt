cmake_minimum_required (VERSION 3.27)

project ("kodik" C)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include (CheckIncludeFile)
include (CheckSymbolExists)
include (Vendor)

option (KODIK_BUILD_TESTS "Build tests" ON)

find_package (Git REQUIRED)

kodik_vendor_threads ()
kodik_vendor_json ()
kodik_vendor_nng ()

check_include_file (stdio.h     HAVE_STDIO_H)
check_include_file (stdint.h    HAVE_STDINT_H)
check_include_file (inttypes.h  HAVE_INTTYPES_H)
check_include_file (stdlib.h    HAVE_STDLIB_H)
check_include_file (string.h    HAVE_STRING_H)

check_include_file (threads.h   HAVE_THREADS_H)
check_include_file (pthread.h   HAVE_PTHREAD_H)

set (CMAKE_C_STANDARD 17)
set (CMAKE_C_EXTENSIONS OFF)
set (CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory (src)

if (KODIK_BUILD_TESTS)
  include (CTest)
  enable_testing ()
  # kodik_vendor_munit ()
  add_subdirectory (tests)
endif ()
