#include "../vendor/unity/unity.h"
#include "sites.h"
#include "db.h"
#include <unistd.h>
#include <signal.h>

void test_save_site(void) {
  int err = save_site("sites_test_db.sqlite3", "Atom Feed", "localhost:3333/atom");
  TEST_ASSERT_EQUAL(err, 0);
  database *db;
  open_db("sites_test_db.sqlite3", &db);
  row * s;
  err = execute_statement(db, "SELECT title, feed_url, base_url, feed_type from sites;", &s);
  TEST_ASSERT_EQUAL(err, 0);
  TEST_ASSERT_EQUAL_STRING("Atom Feed", s->results->value);
  TEST_ASSERT_EQUAL_STRING("http://localhost:3333/atom.xml", s->results->next->value);
  TEST_ASSERT_EQUAL_STRING("http://localhost:3333", s->results->next->next->value);
  TEST_ASSERT_EQUAL(0, (int)s->results->next->next->next->value[0] - '0');
  free_row(s);
  close_db(db);
}

int main(void) {
  UNITY_BEGIN();
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    execve("./fetcher/fetcher_server", NULL, NULL);
  } else {
    sleep(1); // This is hacky and terrible and I should feed bad
    RUN_TEST(test_save_site);
    kill(pid, SIGKILL);
    return UNITY_END();
  }
}
