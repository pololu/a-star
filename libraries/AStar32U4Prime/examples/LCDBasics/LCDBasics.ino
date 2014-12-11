/* This example demonstrates basic use of the A-Star 32U4 Prime
LCD.  It prints the word "hi" on the first line of the LCD and
prints the number 1234 on the second line.

Note: This demo uses the standard A-Star 32U4 Prime LCD pins.
To avoid damage or improper operation, if you have shields or
other electronics connected, make sure they do not use those
pins in a conflicting way. */

#include <AStar32U4Prime.h>

AStar32U4PrimeLCD lcd;

void setup()
{

}

void loop()
{
  // Clear the screen
  lcd.clear();

  // Print a string
  lcd.print("hi");

  // Go to the next line
  lcd.gotoXY(0, 1);

  // Print a number
  lcd.print(1234);

  delay(1000);
}

