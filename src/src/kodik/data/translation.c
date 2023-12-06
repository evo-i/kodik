#include <kodik/memory.h>
#include <kodik/data/translation.h>

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <jansson.h>

#define KODIK_TRANSLATION_FIELD_TITLE ("title")
#define KODIK_TRANSLATION_FIELD_TYPE  ("type")
#define KODIK_TRANSLATION_FIELD_ID    ("id")

struct kodik_translation_t {
  char *psz_title;
  char *psz_type;
  int64_t i_id;
};

kodik_translation_t *
kodik_translation_new(void) {
  return kodik_calloc(1, sizeof(kodik_translation_t));
}

kodik_translation_t *
kodik_translation_new_data_size(char const *title, size_t title_length,
                                char const *type, size_t type_length,
                                int64_t id) {
  kodik_translation_t *translation;
  char *title_copy;
  char *type_copy;

  if (NULL == title
      || 0 >= title_length) {
    return NULL;
  }

  if (NULL == type
      || 0 >= type_length) {
    return NULL;
  }

  title_copy = kodik_calloc(title_length + 1, sizeof(char));
  if (NULL == title_copy) {
    return NULL;
  }

  type_copy = kodik_calloc(type_length + 1, sizeof(char));
  if (NULL == type_copy) {
    kodik_free(title_copy);
    return NULL;
  }

  translation = kodik_translation_new();
  if (NULL == translation) {
    kodik_free(title_copy);
    kodik_free(type_copy);
    return NULL;
  }

  *translation
    = (kodik_translation_t) {
      .psz_title = memmove(title_copy, title, title_length),
      .psz_type = memmove(type_copy, type, type_length),
      .i_id = id
    };

  return translation;
}

kodik_translation_t *
kodik_translation_new_data(char const *title, char const *type, int64_t id) {
  return kodik_translation_new_data_size(title, strlen(title),
                                         type, strlen(type),
                                         id);
}

kodik_translation_t *
kodik_translation_new_from_json(json_t const *root) {
  json_t *j_title;
  json_t *j_type;
  json_t *j_id;
  size_t title_length;
  size_t type_length;
  char const *title;
  char const *type;
  int32_t id;

  j_title = json_object_get(root, KODIK_TRANSLATION_FIELD_TITLE);
  j_type = json_object_get(root, KODIK_TRANSLATION_FIELD_TYPE);
  j_id = json_object_get(root, KODIK_TRANSLATION_FIELD_ID);

  if (NULL == j_title
      || !json_is_string(j_title)
      || NULL == j_type
      || !json_is_string(j_type)
      || NULL == j_id
      || !json_is_integer(j_id)) {
    return NULL;
  }

  title = json_string_value(j_title);
  title_length = json_string_length(j_title);
  type = json_string_value(j_type);
  type_length = json_string_length(j_type);
  id = json_integer_value(j_id);

  return kodik_translation_new_data_size(title, title_length,
                                         type, type_length, id);
}

char const *
kodik_translation_get_title(kodik_translation_t const *translation) {
  return
    translation
      ? translation->psz_title
      : NULL;
}

char const *
kodik_translation_get_type(kodik_translation_t const *translation) {
  return
    translation
      ? translation->psz_type
      : NULL;
}

int64_t
kodik_translation_get_id(kodik_translation_t const *translation) {
  return
    translation
      ? translation->i_id
      : INT64_MIN;
}
