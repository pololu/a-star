/* This example demonstrates three different ways to
interface with a user pushbutton on the Zumo 32U4. */

#include <Wire.h>
#include <Zumo32U4.h>

// These objects provide access to the Zumo 32U4's
// on-board buttons.
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;

void setup()
{
  /* Method 1: Use the waitForButton() function, which blocks and
   * doesn't return until a button press and release are
   * detected. This function takes care of button debouncing. */
  buttonA.waitForButton();
}

void loop()
{
  /* Method 2: Directly read the state of the button with the
   * isPressed() function.  This method is non-blocking and
   * provides no debouncing. */
  bool buttonPressed = buttonB.isPressed();
  if (buttonB.isPressed())
  {
    // Whenever the button is pressed, turn on the yellow LED.
    ledYellow(1);
  }
  else
  {
    // Whenever the button is not pressed, turn off the yellow
    // LED.
    ledYellow(0);
  }

  /* Method 3: Call getSingleDebouncedPress() regularly in a
   * loop, which returns true to report a single button press or
   * false otherwise. This function is non-blocking and takes
   * care of button debouncing. */
  if (buttonC.getSingleDebouncedPress())
  {
    Serial.println(F("Button B was pressed."));
  }

  /* If you use non-blocking functions like isPressed() and
   * getSingleDebouncedPress(), then you can monitor multiple
   * buttons at the same time and also take care of other tasks
   * at the same time.  In this example, we blink the green LED
   * while monitoring the buttons. */
  ledRed(millis() % 1024 < 100);
}
