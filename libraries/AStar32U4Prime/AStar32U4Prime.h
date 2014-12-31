// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

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

/*! \brief Reads the battery voltage for an A-Star 32U4 Prime LV and returns it
in millivolts.

This function performs an analog reading and uses it to compute the voltage on
the A-Star 32U4 Prime LV's VIN pin in millivolts.  This only works if the
specified pin (A1 by default) has been connected to BATLEV.

This function is only meant to be run on the A-Star 32U4 Prime LV (the blue
board) and will give incorrect results on other versions.

@param pin The pin number to read.  This argument is passed on to analogRead.
  The default value is `A1`.

\sa readBatteryMillivoltsSV() */
inline uint16_t readBatteryMillivoltsLV(uint8_t pin = A1)
{
    const uint8_t sampleCount = 8;
    uint16_t sum = 0;
    for (uint8_t i = 0; i < sampleCount; i++)
    {
        sum += analogRead(pin);
    }

    // VBAT = 3 * millivolt reading = 3 * raw * 5000/1024
    //      = raw * 1875 / 128
    // The correction number below makes it so that we round to the nearest
    // whole number instead of always rounding down.
    const uint16_t correction = 64 * sampleCount - 1;
    return ((uint32_t)sum * 1875 + correction) / (128 * sampleCount);
}

/*! \brief Reads the battery voltage for an A-Star 32U4 Prime SV and returns it
in millivolts.

This function performs an analog reading and uses it to compute the voltage on
the A-Star 32U4 Prime SV's VIN pin in millivolts.  This only works if the
specified pin (A1 by default) has been connected to BATLEV.

This function is only meant to be run on the A-Star 32U4 Prime SV (the green
board) and will give incorrect results on other versions.

@param pin The pin number to read.  This argument is passed on to analogRead.
  The default value is `A1`.

\sa readBatteryMillivoltsLV() */
inline uint16_t readBatteryMillivoltsSV(uint8_t pin = A1)
{
    const uint8_t sampleCount = 8;
    uint16_t sum = 0;
    for (uint8_t i = 0; i < sampleCount; i++)
    {
        sum += analogRead(pin);
    }

    // VBAT = 8 * millivolt reading = 8 * raw * 5000/1024
    //      = raw * 625 / 16
    // The correction number below makes it so that we round to the nearest
    // whole number instead of always rounding down.
    const uint16_t correction = 8 * sampleCount - 1;
    return ((uint32_t)sum * 625 + correction) / (16 * sampleCount);
}

/*! \deprecated This function is deprecated and is only here for backwards
compatibility.  We recommend using readBatteryMillivoltsLV() instead. */
inline uint16_t readBatteryMillivolts(uint8_t pin = A1)
{
    return readBatteryMillivoltsLV(pin);
}
