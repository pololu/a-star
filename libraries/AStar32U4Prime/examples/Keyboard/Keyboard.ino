/* This example shows how to turn your A-Star 32U4 Prime into a
simple keyboard.  The three on-board buttons (A, B, and C) can
each be used to type their corresponding letter on your computer.
An extra button can optionally be connected to pin 12 to type the
letter D, or you can just short that pin to GND with a wire.

Be careful when experimenting with this demo!  If you
accidentally change it to send bad keystrokes constantly, then
it could be very hard to reprogram the board.

This example uses the getSingleDebouncedPress function to monitor
for press events on all the buttons simultaneously, with
debouncing.  We did not use getSingleDebouncedRelease to monitor
for release events because there is no strict guarantee that
every debounced button press event would have a corresponding
button release event; the two functions use independent state
machines and sample the button at different times.

Note: This demo uses the standard A-Star 32U4 Prime button pins
and pin 12. To avoid damage or improper operation, if you have
shields or other electronics connected, make sure they do not use
those pins in a conflicting way. */

#include <AStar32U4Prime.h>

// These objects provide access to the A-Star 32U4 Prime's
// on-board buttons:
AStar32U4PrimeButtonA buttonA;
AStar32U4PrimeButtonB buttonB;
AStar32U4PrimeButtonC buttonC;

// We can also define buttons on other pins using the Pushbutton
// class.  Here we use pin 12: the internal pull-up will be
// enabled and the button will be considered to be pressed when
// pin 12 reads low.  To use this, you could connect a momentary
// pushbutton between pin 12 and GND.
Pushbutton buttonD(12);

void setup() {
  Keyboard.begin();
}

void loop() {
  if (buttonA.getSingleDebouncedPress()) { Keyboard.press('a'); }
  if (!buttonA.isPressed()) { Keyboard.release('a'); }

  if (buttonB.getSingleDebouncedPress()) { Keyboard.press('b'); }
  if (!buttonB.isPressed()) { Keyboard.release('b'); }

  if (buttonC.getSingleDebouncedPress()) { Keyboard.press('c'); }
  if (!buttonC.isPressed()) { Keyboard.release('c'); }

  if (buttonD.getSingleDebouncedPress()) { Keyboard.press('d'); }
  if (!buttonD.isPressed()) { Keyboard.release('d'); }
}

