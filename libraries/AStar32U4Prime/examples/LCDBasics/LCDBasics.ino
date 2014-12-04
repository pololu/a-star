/* This example demonstrates basic use of the A-Star 32U4 Prime
LCD.  It prints the word "hi" on the first line of the LCD and
prints the number 1234 on the second line. */

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
  lcd.print("hi ");

  // Go to the next line
  lcd.gotoXY(0, 1);

  // Print a number
  lcd.print(1234);

  delay(1000);
}

