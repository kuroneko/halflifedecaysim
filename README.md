# HalflifeDecaySim

HalflifeDecaySim plots population vs iterations given a specific probability of decay.  This is determined using a trivial monte-carlo simulation.

The app is written using Qt 5.15.0 and can be built as a WASM target so it can run in a desktop browser window and linked from a Moodle instance.

It's most likely not the most efficient thing, since the wasm blob weighs in at 12+MB right now, and I'm sure you could do it in native JS with less code, but I'm more a C++ guy, and I wrote it with the intention of running it directly on desktops.

This toy app came about due to a request from my wife, a science teacher, who wanted a way for her students to play with the parameters easily.  Traditionally this would be done using a number of dice, and eliminating dice from each iteration that met specific criteria.  Computers can do this a lot faster than we can manually. :)

## Suggested Improvements

These are things that were out of scope of my immediate concerns

* There's space to extend the idea to display the data from the monte-carlo simulation for auditing/verification.  The full data is kept until we've finished adding it to the chart, so it should be reasonably easy to do.

* Determine a best-fit curve for the result data and plot that alongside the data on the chart.

* Fine-grained access to control axes scale.

