Feed Reader
===========

An experiment in learning c by making a simple feed reader.

## What does it do?

Right now it can find the feed url for a given site and save it to the named sqlite database.

Example:

```
./feed-reader db.sqlite3 "Peter Debelak" peterdebelak.com
```

## Building

Run `make`.

Has only been built on os x, but could work on linux. Relies on `sqlite3`, `libxml2`, and `curl` being present on the system. Also uses `strdup` which is non-standard and may not be present on some systems.

If you are having problems with libxml2 on os x, you might need to run `brew install libxml2` and `brew link libxml2 --force`.

## Testing

Feed Reader uses [Unity](http://www.throwtheswitch.org/unity/) for testing. Testing the http code uses ruby to run a fake http server so you will need ruby installed on your system to run those tests.

Run `make test` to run tests.
