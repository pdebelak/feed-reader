#include "../vendor/unity/unity.h"
#include "http.h"
#include <unistd.h>
#include <signal.h>

void test_makes_http_request_with_status_code_and_body(void) {
  start_http();
  http_response *resp;
  int err;
  err = http_get_url("localhost:3333/page", &resp);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(200, resp->status_code);
  char * body;
  err = read_http_response_body(resp, &body);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL_STRING("Hello, world!", body);
  free(body);
  free_http_response(resp);
  stop_http();
}

void test_sets_status_code_to_404_for_nonexistant_pages(void) {
  start_http();
  http_response *resp;
  int err;
  err = http_get_url("localhost:3333/fake", &resp);
  TEST_ASSERT_EQUAL(0, err);
  TEST_ASSERT_EQUAL(404, resp->status_code);
  free_http_response(resp);
  stop_http();
}

int main(void) {
  UNITY_BEGIN();
  pid_t pid;
  pid = fork();
  if (pid == 0) {
    execve("./http/http_server", NULL, NULL);
  } else {
    // This is hacky and terrible and I should feed bad, but the server needs
    // time to come up
    sleep(1);
    RUN_TEST(test_makes_http_request_with_status_code_and_body);
    RUN_TEST(test_sets_status_code_to_404_for_nonexistant_pages);
    kill(pid, SIGKILL);
    return UNITY_END();
  }
}
