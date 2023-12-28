macro (kodik_vendor_vcpkg)
  option (VCPKG_MANIFEST_MODE "" ON)
  set (CMAKE_TOOLCHAIN_FILE
        "${CMAKE_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake")
endmacro (kodik_vendor_vcpkg)
