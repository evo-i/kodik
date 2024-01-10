#include <kodik/memory.h>
#include <kodik/data/year.h>

#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <json_object.h>

#define KODIK_YEAR_FIELD_YEAR  ("year")
#define KODIK_YEAR_FIELD_COUNT ("count")

struct kodik_year {
  int64_t i_year;
  int64_t i_count;
};

KODIK_API
struct kodik_year *
kodik_year_new(void) {
  return kodik_calloc(1, sizeof(struct kodik_year));
}

KODIK_API
struct kodik_year *
kodik_year_new_data(int64_t year, int64_t count) {
  struct kodik_year *self;

  self = kodik_year_new();
  if (NULL == self) {
    return NULL;
  }

  *self
    = (struct kodik_year) {
      .i_year = year,
      .i_count = count
    };

  return self;
}

KODIK_API
struct kodik_year *
kodik_year_new_from_json(json_object const *root) {
  json_object *j_year,
              *j_count;

  if (!json_object_object_get_ex(root, KODIK_YEAR_FIELD_YEAR, &j_year)
      || !json_object_object_get_ex(root, KODIK_YEAR_FIELD_COUNT, &j_count)
        || !json_object_is_type(j_year, json_type_int)
        || !json_object_is_type(j_count, json_type_int)) {
    return NULL;
  }

  return kodik_year_new_data(json_object_get_int64(j_year),
                             json_object_get_int64(j_count));
}

int64_t
kodik_year_get_year(struct kodik_year const *year) {
  return
    year
      ? year->i_year
      : INT64_MIN;
}

int64_t
kodik_year_get_count(struct kodik_year const *year) {
  return
    year
      ? year->i_count
      : INT64_MIN;
}

KODIK_API
void
kodik_year_free(struct kodik_year *self) {
  kodik_free(self);
}
