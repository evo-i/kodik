#include <kodik/memory.h>
#include <kodik/data/year.h>

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include <jansson.h>

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
kodik_year_new_from_json(json_t const *root) {
  json_t *j_year;
  json_t *j_count;

  int64_t year;
  int64_t count;

  j_year = json_object_get(root, KODIK_YEAR_FIELD_YEAR);
  j_count = json_object_get(root, KODIK_YEAR_FIELD_COUNT);

  if (NULL == j_year
      || !json_is_integer(j_year)
      || NULL == j_count
      || !json_is_integer(j_count)) {
    return NULL;
  }

  year = json_integer_value(j_year);
  count = json_integer_value(j_count);

  return kodik_year_new_data(year, count);
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
