LINK = gcc -Wall
COMPILE = ${LINK} -c
REMOVE = rm -f

SQLITE_LFLAGS = -l sqlite3
LIBXML_LFLAGS = `xml2-config --libs`
LIBXML_CFLAGS = `xml2-config --cflags`
LIBCURL_LFLAGS = `curl-config --libs`

LFLAGS = ${SQLITE_LFLAGS} ${LIBCURL_LFLAGS} ${LIBXML_LFLAGS}
CFLAGS = ${LIBXML_CFLAGS}

feed-reader: feed-reader.o db.o http.o fetcher.o
	${LINK} feed-reader.o db.o http.o fetcher.o ${LFLAGS} -o feed-reader

feed-reader.o: feed-reader.c db/db.h http/http.h
	${COMPILE} ${CFLAGS} feed-reader.c

db.o: db/db.c db/db.h
	${COMPILE} db/db.c

http.o: http/http.c http/http.h
	${COMPILE} http/http.c

fetcher.o: fetcher/fetcher.c fetcher/fetcher.h http/http.h
	${COMPILE} ${LIBXML_CFLAGS} fetcher/fetcher.c

clean:
	${REMOVE} feed-reader feed-reader.o db.o http.o fetcher.o

test: run_tests clean_test

run_tests: db_test http_test fetcher_test
	./db_test && ./http_test && ./fetcher_test

clean_test:
	${REMOVE} db_test db_test.o http_test http_test.o fetcher_test fetcher_test.o unity.o

unity.o: vendor/unity/unity.c vendor/unity/unity.h
	${COMPILE} vendor/unity/unity.c

db_test: db_test.o db.o unity.o
	${LINK} db_test.o db.o unity.o ${SQLITE_LFLAGS} -o db_test

db_test.o: db/db_test.c db/db.h
	${COMPILE} db/db_test.c

http_test: http_test.o http.o unity.o
	${LINK} http_test.o http.o unity.o ${LIBCURL_LFLAGS} -o http_test

http_test.o: http/http_test.c http/http.h
	${COMPILE} http/http_test.c

fetcher_test: fetcher_test.o fetcher.o http.o unity.o
	${LINK} fetcher_test.o fetcher.o http.o unity.o ${LIBCURL_LFLAGS} ${LIBXML_LFLAGS} ${LIBXML_CFLAGS} -o fetcher_test

fetcher_test.o: fetcher/fetcher_test.c fetcher/fetcher.h http/http.h
	${COMPILE} ${LIBXML_CFLAGS} fetcher/fetcher_test.c
