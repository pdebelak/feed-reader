#include <stdio.h>
#include "db/db.h"
#include "fetcher/fetcher.h"

int main(int argc, char **argv) {
  if (argc !=2) {
    printf("That's not right!\n");
    return 1;
  }
  site *s = fetch_feed_url(argv[1]);
  if (s != NULL) {
    printf("Feed url: %s\n", s->feed_url);
    printf("Base url: %s\n", s->base_url);
    if (s->type == ATOM) {
      printf("Feed type: atom\n");
    } else if (s->type == RSS) {
      printf("Feed type: rss\n");
    }
    free_site(s);
  } else {
    printf("No feed found\n");
    return 1;
  }
  return 0;
}
