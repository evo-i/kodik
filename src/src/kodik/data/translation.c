#include <kodik/memory.h>
#include <kodik/data/translation.h>

#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <json_object.h>

#define KODIK_TRANSLATION_FIELD_TITLE ("title")
#define KODIK_TRANSLATION_FIELD_TYPE  ("type")
#define KODIK_TRANSLATION_FIELD_ID    ("id")

struct kodik_translation_t {
  char *psz_title;
  char *psz_type;
  int64_t i_id;
};

KODIK_API
kodik_translation_t *
kodik_translation_new(void) {
  return kodik_calloc(1, sizeof(kodik_translation_t));
}

KODIK_API
kodik_translation_t *
kodik_translation_new_data_size(char const *title, size_t title_length,
                                char const *type, size_t type_length,
                                int64_t id) {
  kodik_translation_t *self;
  char *title_copy;
  char *type_copy;

  if (NULL == title
      || 0 >= title_length) {
    return NULL;
  }

  if (NULL == type
      || 0 >= type_length) {
    return NULL;
  }

  title_copy = kodik_calloc(title_length + 1, sizeof(char));
  if (NULL == title_copy) {
    return NULL;
  }

  type_copy = kodik_calloc(type_length + 1, sizeof(char));
  if (NULL == type_copy) {
    kodik_free(title_copy);
    return NULL;
  }

  self = kodik_translation_new();
  if (NULL == self) {
    kodik_free(title_copy);
    kodik_free(type_copy);
    return NULL;
  }

  *self
    = (kodik_translation_t) {
      .psz_title = memmove(title_copy, title, title_length),
      .psz_type = memmove(type_copy, type, type_length),
      .i_id = id
    };

  return self;
}

KODIK_API
kodik_translation_t *
kodik_translation_new_data(char const *title, char const *type, int64_t id) {
  return kodik_translation_new_data_size(title, strlen(title),
                                         type, strlen(type),
                                         id);
}

KODIK_API
kodik_translation_t *
kodik_translation_new_from_json(json_object const *root) {
  json_object *j_title,
              *j_type,
              *j_id;

  if (!json_object_object_get_ex(root, KODIK_TRANSLATION_FIELD_TITLE, &j_title)
      || !json_object_object_get_ex(root, KODIK_TRANSLATION_FIELD_TYPE, &j_type)
      || !json_object_object_get_ex(root, KODIK_TRANSLATION_FIELD_ID, &j_id)
        || !json_object_is_type(j_id, json_type_int)
        || !json_object_is_type(j_title, json_type_string)
        || !json_object_is_type(j_type, json_type_string)) {
    return NULL;
  }

  return kodik_translation_new_data_size(json_object_get_string(j_title),
                                         json_object_get_string_len(j_title),
                                         json_object_get_string(j_type),
                                         json_object_get_string_len(j_type),
                                         json_object_get_int64(j_id));
}

char const *
kodik_translation_get_title(kodik_translation_t const *self) {
  return
    self
      ? self->psz_title
      : NULL;
}

char const *
kodik_translation_get_type(kodik_translation_t const *self) {
  return
    self
      ? self->psz_type
      : NULL;
}

int64_t
kodik_translation_get_id(kodik_translation_t const *self) {
  return
    self
      ? self->i_id
      : INT64_MIN;
}

KODIK_API
void
kodik_translation_free(kodik_translation_t *self) {
  if (NULL == self) {
    return;
  }

  kodik_free(self->psz_title);
  kodik_free(self->psz_type);
  kodik_free(self);
}
