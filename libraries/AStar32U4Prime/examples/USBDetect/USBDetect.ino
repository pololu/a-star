/* This example shows how to:

- Detect whether USB power is present.
- Detect whether our USB connection is in the "Configured" state.
- Detect whether a program is connected to the USB virtual
  serial port.

The results are displayed using the three on-board user LEDs and
the LCD.

Note: This demo uses the standard A-Star 32U4 Prime LCD pins.  To
avoid damage or improper operation, if you have shields or other
electronics connected, make sure they do not use those pins in a
conflicting way. */

#include <AStar32U4Prime.h>

AStar32U4PrimeLCD lcd;

void setup()
{

}

void loop()
{
  // usbPowerPresent() is defined in the AStar32U4Prime library
  // and returns true if power from the USB port is detected.
  // It is equivalent to: (USBSTA >> VBUS) & 1
  bool usbPower = usbPowerPresent();

  // USBDevice.configured() is provided by the Arduino core code.
  // It returns true if the our USB connection is in the
  // "Configured" state.  This is the last of several states that
  // the connection goes through when a USB device is connected
  // to a computer.  Being in the "Configured" state means that
  // the device is plugged into a computer that (at least
  // partially) recognizes it.
  bool usbConfigured = USBDevice.configured();

  // The Arduino Serial object can be implicitly converted to a
  // bool which is true if the Arduino core code considers the
  // port to be open.  This is usually used in code like "if
  // (Serial)" and is documented here:
  //
  //   http://arduino.cc/en/Serial/IfSerial
  //
  // Note: This might not work as expected depending on what
  // terminal program you use.
  //
  // Note: Unlike the functions shown above which should take
  // about a microsecond or less, this line of code takes at
  // least 10 milliseconds to run.
  bool portOpen = Serial;

  // Turn on the yellow LED if USB power is present.
  ledYellow(usbPower);

  // Turn on the red LED if USB is configured.
  ledRed(usbConfigured);

  // Turn on the green TX LED if the serial port is open.
  ledGreen(portOpen);

  // Display the results on the LCD every 100 ms.
  static uint16_t lastDisplayTime = 0;
  if ((uint16_t)(millis() - lastDisplayTime) > 100)
  {
    lcd.clear();
    lcd.print(F("Pow="));
    lcd.print(usbPower ? 'Y' : 'N');
    lcd.gotoXY(0, 1);
    lcd.print(F("C="));
    lcd.print(usbConfigured ? 'Y' : 'N');
    lcd.print(F(" O="));
    lcd.print(portOpen ? 'Y' : 'N');
  }
}

