#include <kodik/memory.h>
#include <kodik/data/genre.h>

#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <json_object.h>

#define KODIK_GENRE_FIELD_TITLE ("title")
#define KODIK_GENRE_FIELD_COUNT ("count")

struct kodik_genre_t {
  char    *psz_title;
  int64_t i_count;
};

kodik_genre_t *
kodik_genre_new(void) {
  return kodik_calloc(1, sizeof(kodik_genre_t));
}

kodik_genre_t *
kodik_genre_new_data_size(char const *title, size_t title_length,
                          int64_t count) {
  kodik_genre_t *self;
  char *title_copy;

  if (NULL == title
      || 0 >= title_length) {
    return NULL;
  }

  title_copy = kodik_calloc(title_length + 1, sizeof(char));
  if (NULL == title_copy) {
    return NULL;
  }

  self = kodik_genre_new();
  if (NULL == self) {
    kodik_free(title_copy);
    return NULL;
  }

  *self
    = (kodik_genre_t) {
      .psz_title = memmove(title_copy, title, title_length),
      .i_count = count
    };

  return self;
}

kodik_genre_t *
kodik_genre_new_data(char const *title, int64_t count) {
  return kodik_genre_new_data_size(title, strlen(title), count);
}

kodik_genre_t *
kodik_genre_new_from_json(json_object *root) {
  kodik_genre_t *self;
  json_object *j_title;
  json_object *j_count;
  size_t title_length;
  char const *title;
  int64_t count;

  self = NULL;

  j_title = json_object_object_get(root, KODIK_GENRE_FIELD_TITLE);
  j_count = json_object_object_get(root, KODIK_GENRE_FIELD_COUNT);

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
    return NULL;
  }

  title = json_object_get_string(j_title);
  title_length = json_object_get_string_len(j_title);
  count = json_object_get_int64(j_count);

  self = kodik_genre_new_data_size(title, title_length, count);

  json_object_put(j_count);
  json_object_put(j_title);

  return self;
}

char const *
kodik_genre_get_title(kodik_genre_t const *self) {
  return
    self
      ? self->psz_title
      : NULL;
}

int64_t
kodik_genre_get_count(kodik_genre_t const *self) {
  return
    self
      ? self->i_count
      : INT32_MIN;
}

void
kodik_genre_free(kodik_genre_t *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self);
}
