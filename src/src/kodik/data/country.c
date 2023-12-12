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

KODIK_API
kodik_country_t *
kodik_country_new(void) {
  return kodik_calloc(1, sizeof(kodik_country_t));
}

KODIK_API
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

KODIK_API
kodik_country_t *
kodik_country_new_data(char const *title, int64_t count) {
  return kodik_country_new_data_size(title, strlen(title), count);
}

KODIK_API
kodik_country_t *
kodik_country_new_from_json(json_object const *root) {
  json_object *j_title,
              *j_count;

  if (!json_object_object_get_ex(root, KODIK_COUNTRY_FIELD_TITLE, &j_title)
      || !json_object_object_get_ex(root, KODIK_COUNTRY_FIELD_COUNT, &j_count)
        || !json_object_is_type(j_title, json_type_string)
        || !json_object_is_type(j_count, json_type_int)) {
    return NULL;
  }

  return kodik_country_new_data_size(json_object_get_string(j_title),
                                     json_object_get_string_len(j_title),
                                     json_object_get_int64(j_count));
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

KODIK_API
void
kodik_country_free(kodik_country_t *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self);
}
