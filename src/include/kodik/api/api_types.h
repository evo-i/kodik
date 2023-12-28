#ifndef KODIK_API_TYPES_H
#define KODIK_API_TYPES_H 1

#ifdef __cplusplus
extern "C" {
#endif

typedef enum kodik_api_type_e {
  kodik_api_type_years,
  kodik_api_type_countries,
  kodik_api_type_genres,
  kodik_api_type_v2_qualities,
  kodik_api_type_qualities,
  kodik_api_type_translations,
  kodik_api_type_v2_translations,
  kodik_api_type_search,
  kodik_api_type_list
} kodik_api_type_t;

#ifdef __cplusplus
extern }
#endif

#endif /* KODIK_API_TYPES_H */
