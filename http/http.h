#ifndef FEED_READER_HTTP_CODE
#define FEED_READER_HTTP_CODE

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct http_response {
  long status_code;
  char *url;
  FILE *body;
} http_response;

// start_http initializes the http code. Should only be called once.
void start_http();

// stop_http cleans up the http code. Should be called once for each call to
// start_http.
void stop_http();

// free_response frees resources for an http response.
void free_http_response(http_response *r);

// http_get_url makes a get request to the given url, following any redirects.
// It returns non-zero for an error and sets the status code and body on the
// passed http_response pointer. That http_response must be freed by
// free_http_response to avoid leaking resources.
int http_get_url(char *url, http_response **r);

// read_http_response_body reads the body into the passed in char pointer. That
// char must be freed to avoid leaking resources. Returns non-zero in case of
// an error.
int read_http_response_body(http_response *r, char **body);

#endif
