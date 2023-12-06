#include <kodik/memory.h>
#include <kodik/data/genre.h>

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <jansson.h>

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
  kodik_genre_t *genre;
  char *title_copy;

  if (NULL == title
      || 0 >= title_length) {
    return NULL;
  }

  title_copy = kodik_calloc(title_length + 1, sizeof(char));
  if (NULL == title_copy) {
    return NULL;
  }

  genre = kodik_genre_new();
  if (NULL == genre) {
    kodik_free(title_copy);
    return NULL;
  }

  *genre
    = (kodik_genre_t) {
      .psz_title = memcpy(title_copy, title, title_length),
      .i_count = count
    };

  return genre;
}

kodik_genre_t *
kodik_genre_new_data(char const *title, int64_t count) {
  return kodik_genre_new_data_size(title, strlen(title), count);
}

kodik_genre_t *
kodik_genre_new_from_json(json_t const *root) {
  json_t *j_title;
  json_t *j_count;
  size_t title_length;
  char const *title;
  int64_t count;

  j_title = json_object_get(root, KODIK_GENRE_FIELD_TITLE);
  j_count = json_object_get(root, KODIK_GENRE_FIELD_COUNT);

  if (NULL == j_title
      || !json_is_string(j_title)
      || NULL == j_count
      || !json_is_integer(j_count)) {
    return NULL;
  }

  title = json_string_value(j_title);
  title_length = json_string_length(j_title);
  count = json_integer_value(j_count);

  return kodik_genre_new_data_size(title, title_length, count);
}

char const *
kodik_genre_get_title(kodik_genre_t const *genre) {
  return
    genre
      ? genre->psz_title
      : NULL;
}

int64_t
kodik_genre_get_count(kodik_genre_t const *genre) {
  return
    genre
      ? genre->i_count
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
