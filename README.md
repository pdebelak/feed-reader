Feed Reader
===========

An experiment in learning c by making a simple feed reader.

## Building

Run `make`.

Has only been built on os x, but could work on linux. Relies on `sqlite3` being present on the system. Also uses `strdup` which is non-standard and may not be present on some systems.

## Testing

Feed Reader uses [Unity](http://www.throwtheswitch.org/unity/) for testing.

Run `make test` to run tests.
