/* This example shows how to blink the three user LEDs
on the A-Star 32U4 Prime.

Note: This demo uses the standard A-Star 32U4 Prime LED pins.
To avoid damage or improper operation, if you have shields or
other electronics connected, make sure they do not use those
pins in a conflicting way. */

#include <AStar32U4Prime.h>

void setup()
{

}

void loop()
{
  // Turn the LEDs on.
  ledRed(1);
  ledYellow(1);
  ledGreen(1);

  // Wait for a second.
  delay(1000);

  // Turn the LEDs off.
  ledRed(0);
  ledYellow(0);
  ledGreen(0);

  // Wait for a second.
  delay(1000);
}
