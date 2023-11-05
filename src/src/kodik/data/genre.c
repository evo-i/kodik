#include <kodik/data/genre.h>

#define KODIK_GENRE_FIELD_TITLE ("title")
#define KODIK_GENRE_FIELD_COUNT ("count")

struct kodik_genre_t {
  char    *psz_title;
  int64_t i_count;
};

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
