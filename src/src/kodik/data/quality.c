#include <kodik/memory.h>
#include <kodik/data/quality.h>

#include <stddef.h>
#include <string.h>
#include <json_object.h>

#define KODIK_QUALITY_TITLE_KEY ("title")

/* FIXME:
    NEED OPTIMIZATION WITH MEMORY ALLOCATION...
    MAYBE STRUCT SIZE IS EQUAL TO STRING LENGTH?...
*/

struct kodik_quality {
  char *psz_title;
};

KODIK_API
struct kodik_quality *
kodik_quality_new(void) {
  return kodik_calloc(1, sizeof(struct kodik_quality));
}

KODIK_API
struct kodik_quality *
kodik_quality_new_data_size(char const *title, size_t title_length) {
  struct kodik_quality *quality;

  if (NULL == title
      || 0 == title_length) {
    return NULL;
  }

  quality = kodik_quality_new();
  if (NULL == quality) {
    return NULL;
  }

  quality->psz_title = kodik_calloc(title_length + 1, sizeof(char));

  if (NULL == quality->psz_title) {
    kodik_free(quality);
    return NULL;
  }

  memmove(quality->psz_title, title, title_length);

  return quality;
}

KODIK_API
struct kodik_quality *
kodik_quality_new_data(char const *title) {
  return kodik_quality_new_data_size(title, strlen(title));
}

KODIK_API
struct kodik_quality *
kodik_quality_new_from_json(json_object const *json) {
  json_object *j_title;

  if (!json_object_object_get_ex(json, KODIK_QUALITY_TITLE_KEY, &j_title)
      || !json_object_is_type(j_title, json_type_string)) {
    return NULL;
  }

  return kodik_quality_new_data_size(json_object_get_string(j_title),
                                     json_object_get_string_len(j_title));
}

char const *
kodik_quality_get_title(struct kodik_quality const *quality) {
  return
    quality
      ? quality->psz_title
      : NULL;
}

KODIK_API
void
kodik_quality_free(struct kodik_quality *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self);
}
