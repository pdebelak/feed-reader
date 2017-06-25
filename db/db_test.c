#include "../vendor/unity/unity.h"
#include "db.h"

void test_can_create_table_insert_and_select(void) {
  int exec;
  row *opposites;
  database *db = open_db(":memory:");
  exec = execute_statement(db, "CREATE TABLE opposites (first string, second string);", NULL);
  TEST_ASSERT_EQUAL(0, exec);
  exec = execute_statement(db, "INSERT INTO opposites (first, second) VALUES ('hello', 'goodbye');", NULL);
  TEST_ASSERT_EQUAL(0, exec);
  exec = execute_statement(db, "INSERT INTO opposites (first, second) VALUES ('yes', 'no');", NULL);
  TEST_ASSERT_EQUAL(0, exec);
  exec = execute_statement(db, "SELECT first, second FROM opposites;", &opposites);
  TEST_ASSERT_EQUAL(0, exec);
  TEST_ASSERT_EQUAL_STRING("hello", opposites->results->value);
  TEST_ASSERT_EQUAL_STRING("goodbye", opposites->results->next->value);
  TEST_ASSERT_EQUAL_STRING("yes", opposites->next->results->value);
  TEST_ASSERT_EQUAL_STRING("no", opposites->next->results->next->value);
  TEST_ASSERT_NULL(opposites->next->next);
  TEST_ASSERT_NULL(opposites->results->next->next);
  TEST_ASSERT_NULL(opposites->next->results->next->next);
  free_row(opposites);
  exec = close_db(db);
  TEST_ASSERT_EQUAL(0, exec);
}

void test_returns_non_zero_with_bad_statement(void) {
  database *db = open_db(":memory:");
  int exec = execute_statement(db, "SELECT first, second FROM opposites;", NULL);
  TEST_ASSERT_EQUAL(1, exec);
  exec = close_db(db);
  TEST_ASSERT_EQUAL(0, exec);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_can_create_table_insert_and_select);
  RUN_TEST(test_returns_non_zero_with_bad_statement);
  return UNITY_END();
}
