set (VCPKG_BOOTSTRAP_OPTIONS "-disableMetrics")
option (VCPKG_MANIFEST_MODE "" ON)
set (CMAKE_TOOLCHAIN_FILE
  "${CMAKE_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake")
