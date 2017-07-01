#ifndef FEED_READER_SITES_CODE
#define FEED_READER_SITES_CODE

#include <stdlib.h>
#include <stdio.h>
#include "../fetcher/fetcher.h"
#include "../db/db.h"

// save_site looks up data for a given site and saves it in the given sqlite3
// database. Returns non-zero in case of an error.
int save_site(char *db_name, char *title, char *url);

#endif
