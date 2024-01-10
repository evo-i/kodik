#include <kodik/api/api.h>

#include <config.h>

#include <stdint.h>
#include <evo/threads/threads.h>

#include <nng/nng.h>
#include <nng/supplemental/tls/tls.h>
#include <nng/supplemental/http/http.h>

#include <stdatomic.h>

struct kodik_ref_count {
  mtx_t mutex;
  atomic_ulong ref_count;
};

struct kodik_tls {
  nng_tls_config *config;
  nng_tls_mode mode;
};

struct kodik_http {
  nng_url *base_address;
  nng_http_client *client;
  struct kodik_tls tls;
};

struct kodik_api_t {
  struct kodik_http http;
};
