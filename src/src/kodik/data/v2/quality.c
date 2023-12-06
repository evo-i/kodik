#include <kodik/memory.h>
#include <kodik/data/v2/quality.h>

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <jansson.h>

#define KODIK_V2_QUALITY_FIELD_TITLE ("title")
#define KODIK_V2_QUALITY_FIELD_COUNT ("count")

struct kodik_v2_quality_t {
  char    *psz_title;
  int64_t i_count;
};

kodik_v2_quality_t *
kodik_v2_quality_new(void) {
  return kodik_calloc(1, sizeof(kodik_v2_quality_t));
}

kodik_v2_quality_t *
kodik_v2_quality_new_data_size(char const *title, size_t title_length,
                               int64_t count) {
  kodik_v2_quality_t *self;
  char *title_copy;

  if (NULL == title
      || 0 >= title_length) {
    return NULL;
  }

  title_copy = kodik_calloc(title_length + 1, sizeof(char));
  if (NULL == title_copy) {
    return NULL;
  }

  self = kodik_v2_quality_new();
  if (NULL == self) {
    kodik_free(title_copy);
    return NULL;
  }

  *self
    = (kodik_v2_quality_t) {
      .psz_title = memcpy(title_copy, title, title_length),
      .i_count = count
    };

  return self;
}

kodik_v2_quality_t *
kodik_v2_quality_new_data(char const *title, int64_t count) {
  return kodik_v2_quality_new_data_size(title, strlen(title), count);
}

kodik_v2_quality_t *
kodik_v2_quality_new_from_json(json_t const *root) {
  json_t *j_title;
  json_t *j_count;
  size_t title_length;
  char const *title;
  int64_t count;

  j_title = json_object_get(root, KODIK_V2_QUALITY_FIELD_TITLE);
  j_count = json_object_get(root, KODIK_V2_QUALITY_FIELD_COUNT);

  if (NULL == j_title
      || !json_is_string(j_title)
      || NULL == j_count
      || !json_is_integer(j_count)) {
    return NULL;
  }

  title = json_string_value(j_title);
  title_length = json_string_length(j_title);
  count = json_integer_value(j_count);

  return kodik_v2_quality_new_data_size(title, title_length, count);
}

char const *
kodik_v2_quality_get_title(kodik_v2_quality_t const *self) {
  return
    self
      ? self->psz_title
      : NULL;
}

int64_t
kodik_v2_quality_get_count(kodik_v2_quality_t const *self) {
  return
    self
      ? self->i_count
      : INT32_MIN;
}

void
kodik_v2_quality_free(kodik_v2_quality_t *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self);
}
