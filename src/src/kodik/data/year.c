#include <kodik/data/year.h>

#include <stdint.h>

struct kodik_year_t {
  int64_t i_year;
  int64_t i_count;
};

int64_t
kodik_year_get_year(kodik_year_t const *year) {
  return
    year
      ? year->i_year
      : INT64_MIN;
}

int64_t
kodik_translation_get_counr(kodik_year_t const *year) {
  return
    year
      ? year->i_count
      : INT64_MIN;
}
