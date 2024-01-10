#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>
#include <nng/nng.h>
#include <nng/supplemental/tls/tls.h>
#include <nng/supplemental/http/http.h>

#define CERT_PATH "C:/msys64/home/devbi/git/kodik/ca-bundle.bin"
#define CERT_TRUST_PATH "C:/msys64/home/devbi/git/kodik/ca-bundle.trust.bin"
#define KODIK_SCHEME "https://"
#define KODIK_DOMEN "kodikapi.com"
#define KODIK_REQUEST "/list?token=3e4d4954bdef734c71f1e8190f76b32e"
#define KODIK_FULL_URL KODIK_SCHEME KODIK_DOMEN KODIK_REQUEST

#include "resources/kodik/resource.h"
#include <Windows.h>

void
nng_abort_on_error(int err) {
  if (err != 0) {
    char const *error = nng_strerror(err);
    fprintf(stderr, "[NNG Error]: %s\n", error);
    abort();
  }
}

int
main(int argc, char const *argv[]) {
  HMODULE kodik_module = LoadLibrary("libkodik.dll");

  LPCSTR cert_bundle = MAKEINTRESOURCE(KODIK_IDR_CERTIFICATES_BUNDLE_MZ);

  HRSRC certificate_resource
    = FindResourceA(kodik_module, cert_bundle, "CERTIFICATE");

  DWORD resource_size = SizeofResource(kodik_module, certificate_resource);

  HGLOBAL loaded_resource = LoadResource(kodik_module, certificate_resource);

  LPVOID resource_data = LockResource(loaded_resource);

  char const *res_data = resource_data;

  char *certificate_data = malloc(resource_size + 1);
  memcpy(certificate_data, res_data, resource_size);

  nng_tls_config *tls_config;

  nng_aio *aio;
  nng_url *url;

  nng_http_client *client;
  nng_http_req *req;
  nng_http_res *res;

  int status = 0;

  nng_abort_on_error(nng_tls_config_alloc(&tls_config, NNG_TLS_MODE_CLIENT));
  nng_abort_on_error(nng_tls_config_ca_chain(tls_config, certificate_data, NULL));
  free(certificate_data);
  nng_abort_on_error(nng_tls_config_server_name(tls_config, KODIK_DOMEN));

  nng_abort_on_error(nng_url_parse(&url, KODIK_FULL_URL));

  nng_abort_on_error(nng_http_client_alloc(&client, url));
  nng_abort_on_error(nng_http_client_set_tls(client, tls_config));

  nng_abort_on_error(nng_http_req_alloc(&req, url));

  nng_abort_on_error(nng_http_res_alloc(&res));

  nng_aio_alloc(&aio, NULL, NULL);

  nng_http_client_transact(client, req, res, aio);

  nng_aio_wait(aio);

  nng_abort_on_error(nng_aio_result(aio));

  char *data = NULL;
  size_t data_size = { 0 };

  nng_http_res_get_data(res, (void **)&data, &data_size);

  char *result = malloc(data_size + 1);

  memmove(result, data, data_size);
  *(result + data_size) = '\0';


  json_object *root = json_tokener_parse(result);

  fprintf(stdout, "%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

  json_object_put(root);

  free(result);
  nng_http_res_free(res);
  nng_http_req_free(req);
  nng_http_client_free(client);
  nng_url_free(url);
  nng_tls_config_free(tls_config);

  return 0;
}
