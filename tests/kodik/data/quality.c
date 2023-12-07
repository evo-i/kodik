#include <kodik/data/quality.h>
#include <jansson.h>
#include <errno.h>
#include <string.h>
#include <munit.h>
#include <stdio.h>

#if defined(_MSC_VER)
# pragma warning(disable: 4127)
#endif

extern
kodik_quality_t *
kodik_quality_new_from_json(json_t const *);

extern
void
kodik_quality_free(kodik_quality_t *);

int
main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "No data input file.\n");
    return 1;
  }

  FILE *json_file = fopen(argv[1], "r");

  if (errno != 0) {
    fprintf(stderr, "Failied to open file: %s\nFile path: %s\n", strerror(errno), argv[1]);
  }

  munit_assert_ptr_not_null(json_file);

  json_error_t err = { 0 };
  json_t *json_root = json_loadf(json_file, 0, &err);

  munit_assert_ptr_not_null(json_root);

  munit_assert(json_is_array(json_root));

  json_t *json_cursor = NULL;
  kodik_quality_t *kodik_object = NULL;
  size_t index = 0;

  json_array_foreach(json_root, index, json_cursor) {
    kodik_object = kodik_quality_new_from_json(json_cursor);
    munit_assert_ptr_not_null(kodik_object);

    munit_assert_string_equal(
      kodik_quality_get_title(kodik_object),
      json_string_value(json_object_get(json_cursor, "title"))
    );

    fprintf (stdout, "%s\n", json_dumps(json_cursor, JSON_COMPACT));

    kodik_quality_free(kodik_object);
    kodik_object = NULL;
  }

  json_decref(json_root);
  fclose(json_file);

  return 0;
}
