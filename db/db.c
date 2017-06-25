#include "db.h"

database * open_db(char *db_name) {
  database *db;
  sqlite3_open(db_name, &db);
  return db;
}

int close_db(database * db) {
  return sqlite3_close_v2(db);
}

result * make_result(char *value, char *column_name) {
  result * r = NULL;
  r = malloc(sizeof(result));
  r->next = NULL;
  r->value = value;
  r->column_name = column_name;
  return r;
}

row * make_row() {
  row * r = NULL;
  r = malloc(sizeof(row));
  r->next = NULL;
  r->results = NULL;
  return r;
}

int exec_callback(void* out, int column_count, char **results, char **column_names) {
  if (column_count == 0) return 0;

  row *last = (row *)out;
  while (last->next) {
    last = last->next;
  }
  result *head = make_result(strdup(results[0]), column_names[0]);
  result *current_result = head;
  for (int i=1;i<column_count;i++) {
    result *next_result = make_result(strdup(results[i]), column_names[i]);
    current_result->next = next_result;
    current_result = next_result;
  }
  if (last->results) {
    row *next = make_row();
    next->results = head;
    last->next = next;
  } else {
    last->results = head;
  }
  return 0;
}

void free_results(result *r) {
  if (r == NULL) { return; }
  result *current = r;
  result *next = NULL;
  while (current) {
    next = current->next;
    free(current->value);
    free(current);
    current = next;
  }
}

void free_row(row *r) {
  if (r) { return; }
  row *current = r;
  row *next = NULL;
  while (current) {
    next = current->next;
    free_results(current->results);
    free(current);
    current = next;
  }
}

int execute_statement(database * db, char *stmt, row **rows) {
  row *r;
  int val;
  if (rows == NULL) {
    r = NULL;
  } else {
    r = make_row();
  }
  val = sqlite3_exec(db, stmt, *exec_callback, r, NULL);
  if (rows != NULL) {
    *rows = r;
  }
  return val;
}

void print_rows(row * rows) {
  result * results;
  do {
    results = rows->results;
    do {
      if (results->next) {
        printf("%s|", results->value);
      } else {
        printf("%s\n", results->value);
      }
      results = results->next;
    } while(results);
    rows = rows->next;
  } while (rows);
}
