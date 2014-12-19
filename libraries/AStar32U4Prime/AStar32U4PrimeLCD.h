// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/*! \file AStar32U4PrimeLCD.h */

#pragma once

#include <PololuHD44780.h>
#include <FastGPIO.h>
#include <USBPause.h>
#include <SPIPause.h>

/*! \brief Main class for interfacing with the A-Star 32U4 Prime LCD.
 *
 * This class interfaces with an HD44780-compatible LCD connected to the LCD
 * connector on the A-Star 32U4 Prime.
 *
 * This library is similar to the Arduino
 * [LiquidCrystal library](http://arduino.cc/en/Reference/LiquidCrystal),
 * but it has some extra features needed on the A-Star 32U4 Prime:
 *
 * * This class disables USB interrupts temporarily while writing to the LCD so
 *   that the USB interrupts will not change the RXLED and TXLED pins, which
 *   double as LCD data lines.
 * * This class disables the AVR's hardware SPI module temporarily so that
 *   it can use the PB3/MISO/DB4 pin as an output to control the LCD.
 * * This class restores the RS, DB4, DB5, DB6, and DB7 pins to their previous
 *   states when it is done using them so that those pins can also be used for
 *   other purposes such as controlling LEDs.
 *
 * This class assumes that you are using the default pin mapping that you would
 * get by simply connecting an LCD to the 2x7 LCD connector on the A-Star 32U4
 * Prime:
 *
 * * RS = Pin 7 (PE6)
 * * E = Pin 8 (PB4)
 * * DB4 = Pin 14 (PB3/MISO)
 * * DB5 = Pin 17 (PB0/SS/RXLED)
 * * DB6 = Pin 13 (PC7)
 * * DB7 = PD5/TXLED (which has no official pin number)
 *
 * If you want to control your LCD with different pins, you can edit the line
 * labeled "Pin assignments" in AStar32U4PrimeLCD.h or you can make your own new
 * LCD class in your sketch by copying the code for the AStar32U4PrimeLCD class,
 * which is not very long.
 *
 * This class inherits from the Arduino Print class, so you can call the
 * `print()` function on it with a variety of arguments.  See the
 * [Arduino print() documentation](http://arduino.cc/en/Serial/Print)
 * for more information.
 *
 * For detailed information about HD44780 LCD interface, including what
 * characters can be displayed, see the
 * [HD44780 datasheet](http://www.pololu.com/file/0J72/HD44780.pdf).
 */
class AStar32U4PrimeLCD : public PololuHD44780Base
{
    // Pin assignments.  Change this if you want to remap your pins.
    static const uint8_t rs = 7, e = 8, db4 = 14, db5 = 17, db6 = 13, db7 = IO_D5;

public:

    virtual void initPins()
    {
        FastGPIO::Pin<e>::setOutputLow();
    }

    virtual void send(uint8_t data, bool rsValue, bool only4bits)
    {
        // Temporarily disable the AVR's hardware SPI module; if it is enabled
        // then MISO is forced to be an input, and the Arduino SD library
        // generally leaves it enabled.
        SPIPause spiPause;

        // Temporarily disable USB interrupts because they write some pins
        // we are using as LCD pins.
        USBPause usbPause;

        // Save the state of the RS and data pins.  The state automatically
        // gets restored before this function returns.
        FastGPIO::PinLoan<rs> loanRS;
        FastGPIO::PinLoan<db4> loanDB4;
        FastGPIO::PinLoan<db5> loanDB5;
        FastGPIO::PinLoan<db6> loanDB6;
        FastGPIO::PinLoan<db7> loanDB7;

        // Drive the RS pin high or low.
        FastGPIO::Pin<rs>::setOutput(rsValue);

        // Send the data.
        if (!only4bits) { sendNibble(data >> 4); }
        sendNibble(data & 0x0F);
    }

private:

    void sendNibble(uint8_t data)
    {
        FastGPIO::Pin<db4>::setOutput(data >> 0 & 1);
        FastGPIO::Pin<db5>::setOutput(data >> 1 & 1);
        FastGPIO::Pin<db6>::setOutput(data >> 2 & 1);
        FastGPIO::Pin<db7>::setOutput(data >> 3 & 1);

        FastGPIO::Pin<e>::setOutputHigh();
        _delay_us(1);   // Must be at least 450 ns.
        FastGPIO::Pin<e>::setOutputLow();
        _delay_us(1);   // Must be at least 550 ns.
    }
};

