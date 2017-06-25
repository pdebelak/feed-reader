LINK = gcc -Wall
COMPILE = ${LINK} -c
REMOVE = rm -f

feed-reader: feed-reader.o db.o
	${LINK} feed-reader.o db.o -l sqlite3 -o feed-reader

feed-reader.o: feed-reader.c db/db.h
	${COMPILE} feed-reader.c

db.o: db/db.c db/db.h
	${COMPILE} db/db.c

clean:
	${REMOVE} feed-reader feed-reader.o db.o

test: run_tests clean_test

run_tests: db_test
	./db_test

clean_test:
	${REMOVE} db_test db_test.o unity.o

unity.o: vendor/unity/unity.c vendor/unity/unity.h
	${COMPILE} vendor/unity/unity.c

db_test: db_test.o db.o unity.o
	${LINK} db_test.o db.o unity.o -l sqlite3 -o db_test

db_test.o: db/db_test.c db/db.h
	${COMPILE} db/db_test.c
