#ifndef FEED_READER_FETCHER_CODE
#define FEED_READER_FETCHER_CODE

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libxml/HTMLparser.h>
#include "../http/http.h"
#include "../sites/sites.h"

struct site * fetch_feed_url(char *url);

#endif
