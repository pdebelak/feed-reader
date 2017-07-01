#include "sites.h"

int save_site(char *db_name, char *title, char *url) {
  int err;
  database *db;
  err = open_db(db_name, &db);
  if (err != 0) return err;
  site *s = fetch_feed_url(url);
  s->title = title;
  err = execute_statement(db, "CREATE TABLE IF NOT EXISTS sites (id INTEGER PRIMARY KEY, feed_url STRING, base_url STRING, title STRING, feed_type INTEGER);", NULL);
  if (err != 0) {
    close_db(db);
    return err;
  }
  char stmt[1024];
  sprintf(stmt, "INSERT INTO sites (feed_url, base_url, title, feed_type) VALUES ('%s', '%s', '%s', %d);", s->feed_url, s->base_url, title, s->type);
  err = execute_statement(db, stmt, NULL);
  if (err != 0) {
    close_db(db);
    return err;
  }
  err = close_db(db);
  return err;
}
