#include <stdio.h>
#include "db/db.h"
#include "http/http.h"

int main(int argc, char **argv) {
  if (argc !=2) {
    printf("That's not right!\n");
    return 1;
  }
  http_response *r = NULL;
  http_get_url(argv[1], &r);
  printf("Response had a %ld status_code\n", r->status_code);
  char *body = NULL;
  read_http_response_body(r, &body);
  printf("Read body:\n%s\n", body);
  free(body);
  free_http_response(r);
  return 0;
}
