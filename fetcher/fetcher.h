#ifndef FEED_READER_FETCHER_CODE
#define FEED_READER_FETCHER_CODE

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libxml/HTMLparser.h>
#include "../http/http.h"

typedef enum feed_type {
  ATOM,
  RSS
} feed_type;

typedef struct site {
  char *feed_url;
  char *base_url;
  feed_type type;
} site;

site * fetch_feed_url(char *url);

void free_site(site *s);

#endif
