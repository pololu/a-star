/*! \file AStar32U4Prime.h
 *
 * This is the main header file for the %AStar32U4Prime library.
 * It includes all the other header files provided by the library.
 */

#pragma once

#include <FastGPIO.h>
#include <Pushbutton.h>
#include <AStar32U4PrimeLCD.h>
#include <AStar32U4PrimeBuzzer.h>
#include <AStar32U4PrimeButtons.h>
#include <avr/io.h>
#include <stdint.h>

/*! \brief Turns the red user LED (RX) on or off.

@param on 1 to turn on the LED, 0 to turn it off.

The red user LED is on pin 17, which is also known as PB0, SS, and RXLED.  The
Arduino core code uses this LED to indicate when it receives data over USB, so
it might be hard to control this LED when USB is connected. */
inline void ledRed(bool on)
{
    FastGPIO::Pin<17>::setOutput(!on);
}

/*! \brief Turns the yellow user LED on pin 13 on or off.

@param on 1 to turn on the LED, 0 to turn it off. */
inline void ledYellow(bool on)
{
    FastGPIO::Pin<13>::setOutput(on);
}

/*! \brief Turns the green user LED (TX) on or off.

@param on 1 to turn on the LED, 0 to turn it off.

The green user LED is pin PD5, which is also known as TXLED.  The Arduino core
code uses this LED to indicate when it receives data over USB, so it might be
hard to control this LED when USB is connected. */
inline void ledGreen(bool on)
{
    FastGPIO::Pin<IO_D5>::setOutput(!on);
}

/*! \brief Returns true if USB power is detected.

This function returns true if power is detected on the board's USB port and
returns false otherwise.  It uses the ATmega32U4's VBUS line, which is directly
connected to the power pin of the USB connector.

\sa A method for detecting whether the board's virtual COM port is open:
  http://arduino.cc/en/Serial/IfSerial */
inline bool usbPowerPresent()
{
    return USBSTA >> VBUS & 1;
}

/*! \brief Reads the battery voltage and returns it in millivolts.

This function performs an analog reading on pin A1 and uses it to compute the
voltage on the A-Star 32U4's VIN pin in millivolts.  This only works if A1 has
been connected the BATLEV. */
inline uint16_t readBatteryMillivolts()
{
    // VBAT = 3 * millivolt reading = 3 * raw * 5000/1024
    //      = raw * 1875 / 128
    // The 63 below makes it so that we round to the nearest
    // whole number instead of always rounding down.
    return ((uint32_t)analogRead(A1) * 1875 + 63) / 128;
}
