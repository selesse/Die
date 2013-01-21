Die
===

This is a simple cross-platform command line utility used to shutdown your
computer in a more intuitive way (no need for converting minutes or hours to
seconds anymore!).

This was one of my first C programs and Github repositories.  It's probably not
useful enough to keep anymore (or worth showcasing) but I am keeping it up here
for its historical value to me.

Using die
---------

Compile die (make), (optionally place the binary in your PATH), then:

    die 3m40s

or

    die 7h04s

or even

    die 7h30m25s

If you want to cancel your shutdown, use:

    die abort

Note that on Macs, die abort will only abort the earliest shutdown.
Also note that Macs and Linux require root to shutdown.
