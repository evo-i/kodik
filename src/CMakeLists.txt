cmake_minimum_required (VERSION 3.27)

add_library (kodik
    include/kodik/kodik.h
    include/kodik/memory.h
    include/kodik/exports.h
    include/kodik/data/year.h
    include/kodik/data/genre.h
    include/kodik/data/country.h
    include/kodik/data/quality.h
    include/kodik/data/translation.h
    include/kodik/data/v2/quality.h
    include/kodik/data/v2/translation.h

    include/kodik/api/api.h
    include/kodik/api/api_types.h
    include/kodik/api/object.h

    src/kodik/memory.c
    src/kodik/data/year.c
    src/kodik/data/genre.c
    src/kodik/data/country.c
    src/kodik/data/quality.c
    src/kodik/data/translation.c
    src/kodik/data/v2/quality.c
    src/kodik/data/v2/translation.c

    src/kodik/api/api.c
    src/kodik/api/ref_count.c
    src/kodik/api/object.c)

if (WIN32)
  target_sources (kodik
    PRIVATE
      "../resources/kodik/resource.rc")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_custom_command (OUTPUT cert_bundle.o
    COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/resources/certificates/ && ld -r -b binary -o ${CMAKE_CURRENT_BINARY_DIR}/cert_bundle.o ca-bundle.bin
    COMMAND objcopy --rename-section .data=.rodata,alloc,load,readonly,data,contents ${CMAKE_CURRENT_BINARY_DIR}/cert_bundle.o ${CMAKE_CURRENT_BINARY_DIR}/cert_bundle.o)

  add_library (kodik_cert_bundle
    STATIC
      cert_bundle.o)
  add_library (kodik::cert_bundle
    ALIAS
      kodik_cert_bundle)
endif ()

target_include_directories (kodik
  PUBLIC
    include
  INTERFACE
    include
  PRIVATE
    ${CMAKE_BINARY_DIR})

target_link_libraries (kodik
  PUBLIC
    kodik::threads
    kodik::json-static
    nng::nng)

target_compile_definitions (kodik
  PRIVATE
    -DKODIK_DLL_EXPORTS
    -DHAS_CONFIG)

set_target_properties (kodik
  PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include/"
    C_STANDARD 17
    C_EXTENSIONS OFF
    C_STANDARD_REQUIRED ON
    DEFINE_SYMBOL KODIK_DLL
    C_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1)

if (MSVC)
  set_property (TARGET kodik
    PROPERTY
      MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif ()

configure_file ("${CMAKE_CURRENT_LIST_DIR}/include/config.h.in"
                "${CMAKE_BINARY_DIR}/config.h")
