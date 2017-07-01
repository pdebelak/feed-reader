#ifndef FEED_READER_SITES_CODE
#define FEED_READER_SITES_CODE

#include <stdlib.h>
#include <stdio.h>
#include "../fetcher/fetcher.h"
#include "../db/db.h"

typedef enum feed_type {
  ATOM,
  RSS
} feed_type;

typedef struct site {
  char *feed_url;
  char *base_url;
  char *title;
  feed_type type;
} site;

int save_site(char *db_name, char *title, char *url);

void free_site(site *s);

#endif
