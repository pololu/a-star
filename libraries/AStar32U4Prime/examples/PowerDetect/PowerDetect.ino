/* This example shows how to:

- Measure the voltage on the A-Star 32U4 Prime's VIN pin.
- Detect whether USB power is present.

The results are printed to the LCD and also to the serial
monitor.

This example only works if A1 has been connected to BATLEV.
Also, the power switch needs to be in the "On" position.

This example assumes you are using the A-Star 32U4 Prime LV
(the blue board).  If you are using the A-Star 32U4 Prime
SV instead, see the comment in the code below.

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
  bool usbPower = usbPowerPresent();

  // This example assumes you are using the A-Star 32U4 Prime LV
  // (the blue board).  If you are using the A-Star 32U4 Prime
  // SV, change the "LV" in the line below to "SV".
  uint16_t batteryLevel = readBatteryMillivoltsLV();

  // Print the results to the LCD.
  lcd.clear();
  lcd.print(F("B="));
  lcd.print(batteryLevel);
  lcd.print(F("mV"));
  lcd.gotoXY(0, 1);
  lcd.print(F("USB="));
  lcd.print(usbPower ? 'Y' : 'N');

  // Print the results to the serial monitor.
  Serial.print(F("USB="));
  Serial.print(usbPower ? 'Y' : 'N');
  Serial.print(F(" B="));
  Serial.print(batteryLevel);
  Serial.println(F(" mV"));

  delay(200);
}
