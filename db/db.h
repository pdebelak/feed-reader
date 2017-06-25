#ifndef FEED_READER_DB_CODE
#define FEED_READER_DB_CODE

#include <sqlite3.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Database object
typedef sqlite3 database;

// result represents a single database result. It is a singly linked list with a
// pointer to the next result.
typedef struct result {
  struct result * next;
  char * value;
  char * column_name;
} result;

// row represents a single row of database results. It is a singly linked list
// with a pointer to the next row.
typedef struct row {
  struct row * next;
  result * results;
} row;

// open_db opens a database with given name and returns a pointer to it.
// :memory: can be used for an in-memory database. Must be closed with close_db
// to avoid leaking resources.
database * open_db(char *db_name);

// close_db closes a db. Is a no-op for already closed db.
int close_db(database * db);

// execute_statement executes a given sql statement. If results are desired
// from the statement, a row should be passed in to be used as an out
// parameter. To avoid leaking resources, pass that row to free_row. Returns
// non-zero in the case of an error.
int execute_statement(database * db, char *stmt, row **rows);

// free_row frees resources for a given row object and all attached results.
void free_row(row *r);

// print_rows prints row delimited by pipes.
void print_rows(row * rows);

#endif
