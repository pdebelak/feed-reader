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
    setsid();
    // Using ruby to start a fake server, not sure of a good way to do this.
    system("ruby -e \"require 'webrick'; server = WEBrick::HTTPServer.new(Port: 3333); server.mount_proc('/page') { |req, res| res.body = 'Hello, world!' }; server.start\"");
  } else {
    sleep(1); // This is hacky and terrible and I should feed bad
    RUN_TEST(test_makes_http_request_with_status_code_and_body);
    RUN_TEST(test_sets_status_code_to_404_for_nonexistant_pages);
    kill(pid*-1, SIGKILL);
    return UNITY_END();
  }
}
