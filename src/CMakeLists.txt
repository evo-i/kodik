cmake_minimum_required (VERSION 3.27)

if (DEFINED USE_MIMALLOC)
  if (DEFINED mimalloc_FOUND)
    set (HAS_MIMALLOC_H 1)
  endif ()
endif ()

add_library (kodik
  SHARED
    include/kodik/kodik.h
    include/kodik/memory.h
    include/kodik/exports.h
    include/kodik/data/year.h
    include/kodik/data/genre.h
    include/kodik/data/country.h
    include/kodik/data/quality.h
    include/kodik/data/translation.h

    src/kodik/memory.c
    src/kodik/data/year.c
    src/kodik/data/genre.c
    src/kodik/data/country.c
    src/kodik/data/quality.c
    src/kodik/data/translation.c)

target_include_directories (kodik
  PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}/include/"
    "${CMAKE_BINARY_DIR}")

target_link_libraries (kodik
  PUBLIC
    Threads::Threads
    PkgConfig::json
    $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>
    $<$<BOOL:${HAS_MIMALLOC_H}>:$<IF:$<TARGET_EXISTS:mimalloc-static>,mimalloc-static,mimalloc>>)

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
      MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

configure_file ("${CMAKE_CURRENT_LIST_DIR}/include/config.h.in"
                "${CMAKE_BINARY_DIR}/config.h")
