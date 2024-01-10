#include <utest.h>
#include <json.h>
#include <json_util.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <kodik/memory.h>
#include <kodik/data/quality.h>

#if defined(_MSC_VER)
# pragma warning(disable: 4127)
#endif

FILE *json_file = NULL;

extern
struct kodik_quality *
kodik_quality_new_from_json(json_object const *);

extern
void
kodik_quality_free(struct kodik_quality *);

UTEST(kodik, quality) {
  ASSERT_NE(json_file, NULL);

  fseek(json_file, 0, SEEK_END);
  size_t file_size = ftell(json_file);
  rewind(json_file);

  char *data = kodik_calloc(1, file_size + 1);
  ASSERT_NE_MSG(data, NULL, "Unable to allocate memory.");

  fread(data, 1, file_size, json_file);

  json_tokener *tokener = json_tokener_new();

  ASSERT_NE(tokener, NULL);

  json_tokener_set_flags(tokener, JSON_TOKENER_VALIDATE_UTF8);

  json_object *document = json_tokener_parse_ex(tokener, data, file_size + 1);

  enum json_tokener_error error = json_tokener_get_error(tokener);
  ASSERT_EQ(json_tokener_success, error);
  ASSERT_NE(document, NULL);

  json_object *array = document;
  ASSERT_TRUE(json_object_is_type(array, json_type_array));

  size_t array_size = json_object_array_length(array);
  ASSERT_GT(array_size, 0);

  for (size_t i = 0; i < array_size; i++) {
    json_object *current = json_object_array_get_idx(array, i);
    ASSERT_NE(NULL, current);
    struct kodik_quality *quality = kodik_quality_new_from_json(current);
    ASSERT_NE(NULL, quality);

    json_object *j_count,
                *j_title;

    ASSERT_TRUE(json_object_object_get_ex(current, "title", &j_title));

    ASSERT_STREQ(kodik_quality_get_title(quality), json_object_get_string(j_title));

    fprintf(stdout, "%s\n", json_object_to_json_string_ext(current, JSON_C_TO_STRING_PRETTY));

    kodik_quality_free(quality);
  }

  ASSERT_EQ(json_object_put(document), 1);
}

struct utest_state_s utest_state = {0, 0, 0};

int
main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "No data input file.\n");
    return 1;
  }

  json_file = fopen(argv[1], "r");

  int result = utest_main(argc, argv);

  fclose(json_file);

  return result;
}
