/* This example demonstrates basic use of the A-Star 32U4 Prime
LCD.  It prints the word "hi" on the first line of the LCD and
prints the number 1234 on the second line.

The LCD library uses the following pins to write to the LCD, so
you should make sure that you have not connected those pins to
anything else that might be damaged when they driven high or low:

- pin 7 (PE6)
- pin 8 (PB4)
- pin 14 (PB3/MISO)
- pin 17 (PB0/SS/RXLED)
- pin 13 (PC7)
- PD5/TXLED (which has no official pin number) */

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

