function (kodik_vendor_modules)
  find_package(Git QUIET)
  if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
      message(STATUS "Submodule update")
      execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                      RESULT_VARIABLE GIT_SUBMOD_RESULT)
      if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive
failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
      endif()
    endif()
  endif()

  execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                  OUTPUT_VARIABLE PACKAGE_GIT_VERSION
                  ERROR_QUIET
                  OUTPUT_STRIP_TRAILING_WHITESPACE)

  message (STATUS "${PACKAGE_GIT_VERSION}")

  set (KODIK_MODULES_LIST
      "json-c;threads"
        CACHE INTERNAL "")

  foreach (KODIK_MODULE IN LISTS KODIK_MODULES_LIST)
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/vendor/${KODIK_MODULE}/CMakeLists.txt")
      message(FATAL_ERROR
        "The submodules were not downloaded!
GIT_SUBMODULE was turned off or failed.
Please update submodules and try again.")
    endif()
  endforeach ()
endfunction (kodik_vendor_modules)

function (kodik_vendor_json)
  set (BUILD_TESTING OFF CACHE INTERNAL "Disable json-c testing")
  add_subdirectory ("vendor/json-c" EXCLUDE_FROM_ALL)

  if (TARGET json-c)
    add_library (kodik::json ALIAS json-c)
  endif ()

  if (TARGET json-c-static)
    add_library (kodik::json-static ALIAS json-c-static)
  endif ()
endfunction (kodik_vendor_json)

function (kodik_vendor_threads)
  add_subdirectory ("vendor/threads" EXCLUDE_FROM_ALL)
  if (TARGET threads)
    add_library (kodik::threads ALIAS threads)
  endif ()
endfunction (kodik_vendor_threads)
