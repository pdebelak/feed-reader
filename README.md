Feed Reader
===========

An experiment in learning c by making a simple feed reader.

## Building

Run `make`.

Has only been built on os x, but could work on linux. Relies on `sqlite3` being present on the system. Also uses `strdup` which is non-standard and may not be present on some systems.

If you are having problems with libxml2, you might need to run `brew install libxml2` and `brew link libxml2 --force`.

## Testing

Feed Reader uses [Unity](http://www.throwtheswitch.org/unity/) for testing. Testing the http code uses ruby to run a fake http server so you will need ruby installed on your system to run those tests.

Run `make test` to run tests.
