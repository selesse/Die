Die
===

This is a simple "cross-platform" command line utility used to shutdown your
computer in a more intuitive way (no need for converting seconds to minutes or
hours anymore!).

Using die
---------

Place 'die' in your %PATH (or $PATH), then:

    die 3m40s

or

    die 7h04s

or even

    die 7h30m25s

If you want to cancel your shutdown, use:

    die abort

Note that on Macs, die abort will only abort the earliest shutdown.
