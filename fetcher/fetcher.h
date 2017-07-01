#ifndef FEED_READER_FETCHER_CODE
#define FEED_READER_FETCHER_CODE

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libxml/HTMLparser.h>
#include "../http/http.h"

// feed_type enumerates the possible types of a feed.
typedef enum feed_type {
  ATOM,
  RSS
} feed_type;

// site holds the data for a given site.
typedef struct site {
  char *feed_url;
  char *base_url;
  char *title;
  feed_type type;
} site;

// fetches_feed_url finds the base url, feed type, and feed url for a given
// url and returns a site struct with this data. The site returned must be
// freed with free_site to avoid leaking resources.
struct site * fetch_feed_url(char *url);

// free_site frees the memory for the given site.
void free_site(site *s);

#endif
