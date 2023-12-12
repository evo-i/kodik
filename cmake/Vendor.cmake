function (kodik_vendor_nng)
  set (NNG_TESTS OFF CACHE INTERNAL "Disable nng testing")
  set (NNG_ENABLE_NNGCAT OFF CACHE INTERNAL "Disable NNG cat.")
  add_subdirectory ("vendor/nng" EXCLUDE_FROM_ALL)
endfunction (kodik_vendor_nng)

# function (kodik_vendor_munit)
#   add_subdirectory ("vendor/munit" EXCLUDE_FROM_ALL)
# endfunction (kodik_vendor_munit)

function (kodik_vendor_json)
  set (BUILD_TESTING OFF CACHE INTERNAL "Disable json-c testing")
  add_subdirectory ("vendor/json-c" EXCLUDE_FROM_ALL)
endfunction (kodik_vendor_json)

function (kodik_vendor_threads)

  add_subdirectory ("vendor/threads" EXCLUDE_FROM_ALL)
endfunction (kodik_vendor_threads)
