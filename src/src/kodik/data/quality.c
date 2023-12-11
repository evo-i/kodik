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

struct kodik_quality_t {
  char *psz_title;
};

static
kodik_quality_t *
kodik_quality_new(void) {
  return kodik_calloc(1, sizeof(kodik_quality_t));
}

kodik_quality_t *
kodik_quality_new_data_size(char const *title, size_t title_length) {
  kodik_quality_t *quality;

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

kodik_quality_t *
kodik_quality_new_data(char const *title) {
  return kodik_quality_new_data_size(title, strlen(title));
}

kodik_quality_t *
kodik_quality_new_from_json(json_object *json) {
  kodik_quality_t *self;
  json_object *j_title;
  size_t title_length;
  char const *title;

  self = NULL;

  j_title = json_object_object_get(json, KODIK_QUALITY_TITLE_KEY);

  if (NULL == j_title
      || !json_object_is_type(j_title, json_type_string)) {
    if (NULL != j_title) {
      json_object_put(j_title);
    }
    return NULL;
  }

  title = json_object_get_string(j_title);
  title_length = json_object_get_string_len(j_title);

  self = kodik_quality_new_data_size(title, title_length);

  json_object_put(j_title);

  return self;
}

char const *
kodik_quality_get_title(kodik_quality_t const *quality) {
  return
    quality
      ? quality->psz_title
      : NULL;
}

void
kodik_quality_free(kodik_quality_t *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self);
}
