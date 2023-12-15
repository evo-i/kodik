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

  set (KODIK_MODULES_LIST
      "json-c;nng;threads"
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

function (kodik_vendor_nng)
  set (NNG_TESTS OFF CACHE INTERNAL "Disable nng testing")
  set (NNG_ENABLE_NNGCAT OFF CACHE INTERNAL "Disable NNG cat.")
  add_subdirectory ("vendor/nng" EXCLUDE_FROM_ALL)
endfunction (kodik_vendor_nng)

function (kodik_vendor_json)
  set (BUILD_TESTING OFF CACHE INTERNAL "Disable json-c testing")
  add_subdirectory ("vendor/json-c" EXCLUDE_FROM_ALL)
endfunction (kodik_vendor_json)

function (kodik_vendor_threads)

  add_subdirectory ("vendor/threads" EXCLUDE_FROM_ALL)
endfunction (kodik_vendor_threads)
