#include <kodik/data/translation.h>
#include <kodik/memory.h>
#include <json.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <munit.h>

#if defined(_MSC_VER)
# pragma warning(disable: 4127)
#endif

extern
kodik_translation_t *
kodik_translation_new_from_json(json_object *);

extern
void
kodik_translation_free(kodik_translation_t *);

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

  fseek(json_file, 0, SEEK_END);
  size_t file_length = ftell(json_file);
  rewind(json_file);

  char *data = kodik_calloc(file_length + 1, 1);
  munit_assert_ptr_not_null(data);

  size_t readed = fread(data, 1, file_length, json_file);

  json_tokener *tokener = json_tokener_new();
  json_tokener_set_flags(tokener, JSON_TOKENER_VALIDATE_UTF8);

  json_object *json_root = json_tokener_parse_ex(tokener, data, file_length + 1);

  enum json_tokener_error err = json_tokener_get_error(tokener);

  char const * error = json_tokener_error_desc(err);

  kodik_free(data);

  munit_assert_ptr_not_null(json_root);

  json_object *json_cursor = NULL;
  kodik_translation_t *kodik_object = NULL;
  size_t array_length = 0;
  size_t index = 0;

  array_length = json_object_array_length(json_root);

  for (index = 0; index < array_length; index++) {
    json_cursor = json_object_array_get_idx(json_root, index);
    kodik_object = kodik_translation_new_from_json(json_cursor);
    munit_assert_ptr_not_null(kodik_object);

    json_object *j_id;
    json_object *j_title;
    json_object *j_type;

    json_object_object_get_ex(json_cursor, "id", &j_id);
    json_object_object_get_ex(json_cursor, "title", &j_title);
    json_object_object_get_ex(json_cursor, "type", &j_type);

    enum json_type t_id = json_object_get_type(j_id);
    enum json_type t_title = json_object_get_type(j_title);
    enum json_type t_type = json_object_get_type(j_type);

    int64_t tmp = json_object_get_int64(j_id);

    munit_assert_int64(
      kodik_translation_get_id(kodik_object),
      ==,
      json_object_get_int64(j_id)
    );

    munit_assert_string_equal(
      kodik_translation_get_title(kodik_object),
      json_object_get_string(j_title)
    );

    munit_assert_string_equal(
      kodik_translation_get_type(kodik_object),
      json_object_get_string(j_type)
    );

    fprintf (stdout, "%s\n", json_object_to_json_string_ext(json_cursor, JSON_C_TO_STRING_PRETTY));

    kodik_translation_free(kodik_object);
    kodik_object = NULL;
  }

  json_object_put(json_root);
  fclose(json_file);

  return 0;
}
