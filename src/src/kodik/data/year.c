#include <kodik/memory.h>
#include <kodik/data/year.h>

#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <json_object.h>

#define KODIK_YEAR_FIELD_YEAR  ("year")
#define KODIK_YEAR_FIELD_COUNT ("count")

struct kodik_year_t {
  int64_t i_year;
  int64_t i_count;
};

static
kodik_year_t *
kodik_year_new(void) {
  return kodik_calloc(1, sizeof(kodik_year_t));
}

kodik_year_t *
kodik_year_new_data(int64_t year, int64_t count) {
  kodik_year_t *self;

  self = kodik_year_new();
  if (NULL == self) {
    return NULL;
  }

  *self
    = (kodik_year_t) {
      .i_year = year,
      .i_count = count
    };

  return self;
}

kodik_year_t *
kodik_year_new_from_json(json_object *root) {
  kodik_year_t *self;
  json_object *j_year;
  json_object *j_count;

  int64_t year;
  int64_t count;

  self = NULL;

  j_year = json_object_object_get(root, KODIK_YEAR_FIELD_YEAR);
  j_count = json_object_object_get(root, KODIK_YEAR_FIELD_COUNT);

  if (NULL == j_year
      || !json_object_is_type(j_year, json_type_int)
      || NULL == j_count
      || !json_object_is_type(j_count, json_type_int)) {
    if (NULL != j_count) {
      json_object_put(j_count);
    }
    if (NULL != j_year) {
      json_object_put(j_year);
    }
    return self;
  }

  year = json_object_get_int64(j_year);
  count = json_object_get_int64(j_count);

  self = kodik_year_new_data(year, count);

  json_object_put(j_count);
  json_object_put(j_year);

  return self;
}

int64_t
kodik_year_get_year(kodik_year_t const *year) {
  return
    year
      ? year->i_year
      : INT64_MIN;
}

int64_t
kodik_year_get_count(kodik_year_t const *year) {
  return
    year
      ? year->i_count
      : INT64_MIN;
}

void
kodik_year_free(kodik_year_t *self) {
  kodik_free(self);
}
