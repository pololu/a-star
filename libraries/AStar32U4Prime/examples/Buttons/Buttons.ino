/* This example demonstrates three different methods for
detecting a button press and release.  It blinks the green user
LED each time button A is pressed and released.

Note: This demo uses the standard A-Star 32U4 Prime button pins.
To avoid damage or improper operation, if you have shields or
other electronics connected, make sure they do not use those
pins in a conflicting way. */

#include <AStar32U4Prime.h>

// These objects provide access to the A-Star 32U4 Prime's
// on-board buttons.  We will only use buttonA.
AStar32U4PrimeButtonA buttonA;
AStar32U4PrimeButtonB buttonB;
AStar32U4PrimeButtonC buttonC;

void setup()
{

}

void loop()
{
  /* Method 1: Directly read the state of the button with the
   * isPressed() function. You must debounce the button yourself
   * with this method. */
  do
  {
    while (!buttonA.isPressed());  // wait for button to be pressed
    delay(10);                     // debounce the button press
  }
  while (!buttonA.isPressed());    // if button isn't still pressed, loop

  do
  {
    while (buttonA.isPressed());   // wait for button to be released
    delay(10);                     // debounce the button release
  }
  while (buttonA.isPressed());     // if button isn't still released, loop

  // blink LED
  ledGreen(1);
  delay(200);
  ledGreen(0);

  /* Method 2: Use the waitForButton() function, which blocks and
   * doesn't return until a button press and release are
   * detected. This function takes care of button debouncing. */
  buttonA.waitForButton();

  // blink LED
  ledGreen(1);
  delay(200);
  ledGreen(0);

  /* Method 3: Call the getSingleDebouncedRelease() function
   * repeatedly in a loop, which returns true to report a single
   * button release or false otherwise. This function takes care
   * of button debouncing. If you have multiple buttons, you can
   * call getSingleDebouncedRelease() or
   * getSingleDebouncedPress() in a loop for all of them until
   * one of them returns true. */
  while (1)
  {
    if (buttonA.getSingleDebouncedRelease())
    {
      // blink LED
      ledGreen(1);
      delay(200);
      ledGreen(0);
      break;
    }
  }
}
