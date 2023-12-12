function(kodik_make_data_test NAME)
  string(REPLACE "/" "_" SRC ${NAME})

  set (CURRENT_TEST_EXEC_NAME ${SRC}_test)

  add_executable (
    ${CURRENT_TEST_EXEC_NAME}
    kodik/data/${NAME}.c
  )

  target_link_libraries (
    ${CURRENT_TEST_EXEC_NAME}
    PRIVATE
      kodik
      munit
      json-c)

  add_test (
    NAME "kodik ${NAME}"
    COMMAND "${CURRENT_TEST_EXEC_NAME}"
            "${CMAKE_CURRENT_LIST_DIR}/data/${NAME}.json"
  )
endfunction(kodik_make_data_test NAME)

kodik_make_data_test (year)
kodik_make_data_test (genre)
kodik_make_data_test (country)
kodik_make_data_test (quality)
kodik_make_data_test (translation)
kodik_make_data_test (v2/quality)
kodik_make_data_test (v2/translation)
