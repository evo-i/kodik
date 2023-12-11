#include <kodik/memory.h>
#include <kodik/data/country.h>

#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <json.h>
#include <json_object.h>
#include <json_tokener.h>

#define KODIK_COUNTRY_FIELD_TITLE ("title")
#define KODIK_COUNTRY_FIELD_COUNT ("count")

struct kodik_country_t {
  char *psz_title;
  int64_t i_count;
};

kodik_country_t *
kodik_country_new(void) {
  return kodik_calloc(1, sizeof(kodik_country_t));
}

kodik_country_t *
kodik_country_new_data_size(char const *title, size_t title_length,
                            int64_t count) {
  kodik_country_t *self;
  char *title_copy;

  if (NULL == title
      || 0 >= title_length) {
    return NULL;
  }

  title_copy = kodik_calloc(title_length + 1, sizeof(char));
  if (NULL == title_copy) {
    return NULL;
  }

  self = kodik_country_new();
  if (NULL == self) {
    kodik_free(title_copy);
    return NULL;
  }

  *self
    = (kodik_country_t) {
      .psz_title = memmove(title_copy, title, title_length),
      .i_count = count
    };

  return self;
}

kodik_country_t *
kodik_country_new_data(char const *title, int64_t count) {
  return kodik_country_new_data_size(title, strlen(title), count);
}

kodik_country_t *
kodik_country_new_from_json(json_object *root) {
  kodik_country_t *self;
  json_object *j_title;
  json_object *j_count;
  size_t title_length;
  char const *title;
  int64_t count;

  self = NULL;

  j_title = json_object_object_get(root, KODIK_COUNTRY_FIELD_TITLE);
  j_count = json_object_object_get(root, KODIK_COUNTRY_FIELD_COUNT);

  if (NULL == j_title
      || !json_object_is_type(j_title, json_type_string)
      || NULL == j_count
      || !json_object_is_type(j_count, json_type_int)) {
    if (NULL != j_count) {
      json_object_put(j_count);
    }
    if (NULL != j_title) {
      json_object_put(j_title);
    }
    return self;
  }

  title = json_object_get_string(j_title);
  title_length = json_object_get_string_len(j_title);
  count = json_object_get_int64(j_count);

  self = kodik_country_new_data_size(title, title_length, count);

  json_object_put(j_count);
  json_object_put(j_title);

  return self;
}

char const *
kodik_country_get_title(kodik_country_t const *country) {
  return
    country
      ? country->psz_title
      : NULL;
}

int64_t
kodik_country_get_count(kodik_country_t const *country) {
  return
    country
      ? country->i_count
      : INT64_MIN;
}

void
kodik_country_free(kodik_country_t *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self);
}
