#include "../vendor/unity/unity.h"
#include "fetcher.h"
#include <unistd.h>
#include <signal.h>

void test_fetches_rss_feed_url(void) {
  site * s = fetch_feed_url("localhost:3333/rss");
  TEST_ASSERT_EQUAL_STRING("https://example.com/rss.xml", s->feed_url);
  TEST_ASSERT_EQUAL_STRING("http://localhost:3333", s->base_url);
  TEST_ASSERT_EQUAL(RSS, s->type);
  free_site(s);
}

void test_fetches_atom_feed_url(void) {
  site * s = fetch_feed_url("localhost:3333/atom");
  TEST_ASSERT_EQUAL_STRING("http://localhost:3333/atom.xml", s->feed_url);
  TEST_ASSERT_EQUAL_STRING("http://localhost:3333", s->base_url);
  TEST_ASSERT_EQUAL(ATOM, s->type);
  free_site(s);
}

void test_handles_no_feed_url(void) {
  site * s = fetch_feed_url("localhost:3333/neither");
  TEST_ASSERT_EQUAL(NULL, s);
}

int main(void) {
  UNITY_BEGIN();
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    execve("./fetcher/fetcher_server", NULL, NULL);
  } else {
    sleep(1); // This is hacky and terrible and I should feed bad
    RUN_TEST(test_fetches_rss_feed_url);
    RUN_TEST(test_fetches_atom_feed_url);
    RUN_TEST(test_handles_no_feed_url);
    kill(pid, SIGKILL);
    return UNITY_END();
  }
}
