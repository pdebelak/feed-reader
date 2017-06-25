#include <stdio.h>
#include "db/db.h"

int main(int argc, char **argv) {
  if (argc !=2) {
    printf("That's not right!\n");
    return 1;
  }
  database *db = open_db(argv[1]);
  execute_statement(db, "CREATE TABLE IF NOT EXISTS opposites (first string, second string);", NULL);
  execute_statement(db, "INSERT INTO opposites (first, second) VALUES ('hello', 'goodbye');", NULL);
  execute_statement(db, "INSERT INTO opposites (first, second) VALUES ('yes', 'no');", NULL);
  execute_statement(db, "INSERT INTO opposites (first, second) VALUES ('up', 'down');", NULL);
  execute_statement(db, "INSERT INTO opposites (first, second) VALUES ('awake', 'asleep');", NULL);
  row *opposites;
  execute_statement(db, "SELECT first, second FROM opposites;", &opposites);
  print_rows(opposites);
  free_row(opposites);
  execute_statement(db, "DELETE from opposites;", NULL);
  close_db(db);
  return 0;
}
