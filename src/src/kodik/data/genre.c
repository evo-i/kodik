#include <kodik/memory.h>
#include <kodik/data/genre.h>

#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <json_object.h>

#define KODIK_GENRE_FIELD_TITLE ("title")
#define KODIK_GENRE_FIELD_COUNT ("count")

struct kodik_genre {
  char    *psz_title;
  int64_t i_count;
};

KODIK_API
struct kodik_genre *
kodik_genre_new(void) {
  return kodik_calloc(1, sizeof(struct kodik_genre));
}

KODIK_API
struct kodik_genre *
kodik_genre_new_data_size(char const *title, size_t title_length,
                          int64_t count) {
  struct kodik_genre *self;
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
    = (struct kodik_genre) {
      .psz_title = memmove(title_copy, title, title_length),
      .i_count = count
    };

  return self;
}

KODIK_API
struct kodik_genre *
kodik_genre_new_data(char const *title, int64_t count) {
  return kodik_genre_new_data_size(title, strlen(title), count);
}

KODIK_API
struct kodik_genre *
kodik_genre_new_from_json(json_object *root) {
  json_object *j_title,
              *j_count;

  if (!json_object_object_get_ex(root, KODIK_GENRE_FIELD_TITLE, &j_title)
      || !json_object_object_get_ex(root, KODIK_GENRE_FIELD_COUNT, &j_count)
        || !json_object_is_type(j_title, json_type_string)
        || !json_object_is_type(j_count, json_type_int)) {
    return NULL;
  }

  return kodik_genre_new_data_size(json_object_get_string(j_title),
                                   json_object_get_string_len(j_title),
                                   json_object_get_int64(j_count));
}

char const *
kodik_genre_get_title(struct kodik_genre const *self) {
  return
    self
      ? self->psz_title
      : NULL;
}

int64_t
kodik_genre_get_count(struct kodik_genre const *self) {
  return
    self
      ? self->i_count
      : INT32_MIN;
}

KODIK_API
void
kodik_genre_free(struct kodik_genre *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self);
}
