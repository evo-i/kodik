#include <kodik/memory.h>
#include <kodik/data/v2/translation.h>

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <jansson.h>

#define KODIK_V2_TRANSLATION_FIELD_ID    ("id")
#define KODIK_V2_TRANSLATION_FIELD_TITLE ("title")
#define KODIK_V2_TRANSLATION_FIELD_COUNT ("count")

struct kodik_v2_translation_t {
  int64_t i_id;
  char *psz_title;
  int64_t i_count;
};

kodik_v2_translation_t *
kodik_v2_translation_new(void) {
  return kodik_calloc(1, sizeof(kodik_v2_translation_t));
}

kodik_v2_translation_t *
kodik_v2_translation_new_data_size(int64_t id,
                                char const *title,
                                size_t title_length,
                                int64_t count) {
  kodik_v2_translation_t *self;
  char *title_copy;

  if (NULL == title
      || 0 >= title_length) {
    return NULL;
  }

  title_copy = kodik_calloc(title_length + 1, sizeof(char));
  if (NULL == title_copy) {
    return NULL;
  }

  self = kodik_v2_translation_new();
  if (NULL == self) {
    kodik_free(title_copy);
    return NULL;
  }

  *self
    = (kodik_v2_translation_t) {
      .i_id = id,
      .psz_title = memmove(title_copy, title, title_length),
      .i_count = count
    };

  return self;
}

kodik_v2_translation_t *
kodik_v2_translation_new_data(int64_t id, char const *title, int64_t count) {
  return kodik_v2_translation_new_data_size(id, title, strlen(title), count);
}

kodik_v2_translation_t *
kodik_v2_translation_new_from_json(json_t const *root) {
  json_t *j_id;
  json_t *j_title;
  json_t *j_count;
  int64_t id;
  char const *title;
  size_t title_length;
  int64_t count;

  j_id = json_object_get(root, KODIK_V2_TRANSLATION_FIELD_ID);
  j_title = json_object_get(root, KODIK_V2_TRANSLATION_FIELD_TITLE);
  j_count = json_object_get(root, KODIK_V2_TRANSLATION_FIELD_COUNT);

  if (NULL == j_title
      || !json_is_string(j_title)
      || NULL == j_count
      || !json_is_integer(j_count)
      || NULL == j_id
      || !json_is_integer(j_id)) {
    return NULL;
  }


  id = json_integer_value(j_id);
  title = json_string_value(j_title);
  title_length = json_string_length(j_title);
  count = json_integer_value(j_count);

  return kodik_v2_translation_new_data_size(id, title, title_length, count);
}

int64_t
kodik_v2_translation_get_count(kodik_v2_translation_t const *self) {
  return
    self
      ? self->i_count
      : INT64_MIN;
}

char const *
kodik_v2_translation_get_title(kodik_v2_translation_t const *self) {
  return
    self
      ? self->psz_title
      : NULL;
}

int64_t
kodik_v2_translation_get_id(kodik_v2_translation_t const *self) {
  return
    self
      ? self->i_id
      : INT64_MIN;
}

void
kodik_v2_translation_free(kodik_v2_translation_t *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self);
}
