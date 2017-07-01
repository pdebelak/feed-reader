#include <stdio.h>
#include "sites/sites.h"
#include "fetcher/fetcher.h"

int main(int argc, char **argv) {
  if (argc != 4) {
    printf("That's not right! Usage: feed-reader dbname sitename siteurl\n");
    return 1;
  }
  int err = save_site(argv[1], argv[2], argv[3]);
  if (err != 0) {
    printf("Something went wrong saving in the site D:\n");
    return 1;
  }
  return 0;
}
