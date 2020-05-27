# HalflifeDecaySim

HalflifeDecaySim plots population vs iterations given a specific probability of
decay (given as a decimal between 0.0 and 1.0).  This is determined using a 
trivial simulation using a uniform random number distribution.

This toy app came about due to a request from my wife, a science teacher, who 
wanted a way for her students to play with the parameters easily.

## As an Experiment

Traditionally this would be done using a number of dice, and eliminating dice 
from each iteration that met specific criteria.

Rolling 10 dice, and eliminating all results of 1, 2 and 3 would be the same
as an initial population of 10, with a p of 0.5 (assuming a perfect die).

Computers can do this much faster and in a far more abritrary manner, so our
default starting population is 1000, and we accept any valid value for p, not
just 1/6th values...


## On Experimental Error

 * p is handled entirely using double precision floating point numbers - error
   in FP precision should be contained to be no more than 10<sup>-15</sup> or so.  
   "[floating point](https://en.wikipedia.org/wiki/Floating-point_arithmetic)" 
   numbers are based on powers of 2 internally, rather than powers of 10 - there
   is a slight mismatch between the bases that means there's always a bit of
   rounding and representational error created -
   [double precision](https://en.wikipedia.org/wiki/Double-precision_floating-point_format)
   uses a mantissa of 52 bits, which gives precision to approximately 15 decimal
   places.

 * As the quality of the dice affects the conventional experiment, the quality
   of the results are entirely dependent upon the quality of the random number 
   generator.  The code uses the
   [Qt5 Random Number Generator](https://doc.qt.io/qt-5/qrandomgenerator.html#details)
   exclusively with a
   ["cryptographically secure" seed](https://doc.qt.io/qt-5/qrandomgenerator.html#securelySeeded).
   The documentation also implies that the random number distribution is 
   uniform, but it is not actually guarnateed. 
   [Random Number Generation is non-trivial for a computer](https://engineering.mit.edu/engage/ask-an-engineer/can-a-computer-generate-a-truly-random-number/) and can
   impact the results of an activity like this where randomness is assumed.
   In theory, a faulty random number generator could result in the p being
   skewed more than the 10<sup>-15</sup> floating point error.

 * Splines in the chart will occasionally do odd things and vary the 
   interpolation in odd ways, paritucularly where the gradient of the curve 
   changes dramatically.  (Visible with a p of 1.0).  You can disable splines in
   the settings, but then you'll need to apply your own smoothing to the data if
   the line isn't relatively smooth.

## The Software

The app is written using the Qt framework and can be built using the open-source
Qt5 SDK available from https://www.qt.io/.  It has been developed and tested
using version 5.15.0.

It also can be build using emscripten and the WebAssembler target, which is how
the associated web version was built.

If you want to change it, I strongly advise you read the limitations on the
WebAssembler implementation of Qt first, and make your changes using the 
desktop target with that in mind.

### On Web Embedding

It's most likely not the most efficient thing, since the wasm blob weighs in at 
12+MB right now, and I'm sure you could do it in native JS with less code, but
I'm a C++ guy, and I wrote it with the intention of running it directly on
desktops.

### Suggested Improvements

These are things that were out of scope of my immediate concerns

* There's space to extend the idea to display the data from the simulation for
  auditing/verification.  The full data is kept until we've finished adding it
  to the chart, so it should be reasonably easy to do.

* Determine a best-fit curve for the result data and plot that alongside the 
  data on the chart.

* Fine-grained access to control axes scale - right now it always uses the 
  limits set in the settings, and always 11 subdivisions (which works ideally
  with factors of 10).

## License

This software uses features from Qt that are licensed under the GPL, and as 
such, is released under the GPL itself.

Please see COPYING.md for more information.

    HalflifeDecaySim: A Simple App to Model Radioactive Decay
    Copyright (C) 2020 Chris Collins

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

