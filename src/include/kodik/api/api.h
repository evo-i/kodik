#ifndef KODIK_API_H
#define KODIK_API_H 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "../exports.h"
#include "api_types.h"

struct kodik_api;

KODIK_API
struct kodik_api *
kodik_api_new(char const *token);

KODIK_API
void *
kodik_api_get(enum kodik_api_type_e type);

KODIK_API
void
kodik_api_free(struct kodik_api *api);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KODIK_API_H */
