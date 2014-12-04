/* This example shows how to blink the three user LEDs
on the A-Star 32U4 Prime. */

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
