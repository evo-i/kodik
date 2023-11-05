#include <kodik/data/translation.h>

#include <stdint.h>

struct kodik_translation_t {
  char *psz_title;
  char *psz_type;
  int64_t i_id;
};

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
