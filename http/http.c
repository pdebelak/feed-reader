#include "http.h"

void start_http() {
  curl_global_init(CURL_GLOBAL_ALL);
}

void stop_http() {
  curl_global_cleanup();
}

void free_http_response(http_response *r) {
  fclose(r->body);
  free(r);
}

int http_get_url(char *url, http_response **resp) {
  http_response *r = NULL;
  FILE *fp = tmpfile();
  if (fp == NULL) {
    return 1;
  }
  CURL *curl = curl_easy_init();
  if (curl == NULL) {
    return 1;
  }
  CURLcode code;
  code = curl_easy_setopt(curl, CURLOPT_URL, url);
  if (code != CURLE_OK) {
    return code;
  }
  code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  if (code != CURLE_OK) {
    return code;
  }
  code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  if (code != CURLE_OK) {
    return code;
  }
  code = curl_easy_perform(curl);
  if (code != CURLE_OK) {
    return code;
  }
  long status_code = 0;
  code = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
  if (code != CURLE_OK) {
    return code;
  }
  r = malloc(sizeof(http_response));
  if (r == NULL) return 1;
  r->body = fp;
  r->status_code = status_code;
  *resp = r;
  curl_easy_cleanup(curl);
  return 0;
}

int read_http_response_body(http_response *r, char **b) {
  // Implementation mostly copied from lfzawacki's answer on stack overflow
  // found at https://stackoverflow.com/a/3464656/3945932
  char *buffer = NULL;
  FILE *body = r->body;
  if (!body) return 1;
  fseek(body, 0, SEEK_END);
  int string_size = ftell(body);
  rewind(body);
  buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
  int read_size = fread(buffer, sizeof(char), string_size, body);
  if (string_size != read_size) {
    free(buffer);
    return 1;
  }
  buffer[string_size] = '\0';
  rewind(body);
  *b = buffer;
  return 0;
}
