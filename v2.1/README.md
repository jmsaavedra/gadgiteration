gadgIteration hardware v2.1
=============

###digital pinouts###

* D2  - Button "MODE"
* D4  - Button "RANGE"
* D6  - LED Strip
* D7  - MODE LEDs (high=right ON, low=left ON)
* D8  - speaker/audio output
* D13 - onboard green LED

###analog pinouts###

* A0 - Standard Alligator In
* A1 - Human Circuit In
* A2 - SENSOR 1
* A3 - SENSOR 2
* A4 - SENSOR 3

###known bugs, updates for v2.2 or v3.0###

* PWR switch should be implemented, if we want an external power switch on enclosure.
* RANGE button should be moved to D3, so that we can use it as an interrupt
  * [attachInterrupts](http://arduino.cc/en/Reference/attachInterrupt)