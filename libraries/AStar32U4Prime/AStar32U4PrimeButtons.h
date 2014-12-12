// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/** \file AStar32U4PrimeButtons.h */

#pragma once

#include <Pushbutton.h>
#include <FastGPIO.h>
#include <USBPause.h>
#include <SPIPause.h>
#include <util/delay.h>

/*! The pin number for the pin connected to button A on the A-Star 32U4
 *  Prime. */
#define A_STAR_32U4_PRIME_BUTTON_A 14

/*! The pin number for the pin connected to button B on the A-Star 32U4 Prime.
 *  Note that this is not an official Arduino pin number so it cannot be used
 *  with functions like digitalRead, but it can be used with the FastGPIO
 *  library. */
#define A_STAR_32U4_PRIME_BUTTON_B IO_D5

/*! The pin number for the pin connected to button C on the A-Star 32U4
 *  Prime. */
#define A_STAR_32U4_PRIME_BUTTON_C 17

/*! \brief Interfaces with button A on the A-Star 32U4 Prime.
 *
 * The pin used for button A is also used for reading the DO pin on the microSD
 * card.  If the chip select (CS) pin for the microSD card is low (active), you
 * cannot read button A because the signal from the microSD card will override
 * the signal from the button.  Therefore, the CS pin needs to be high whenever
 * functions in this class are called.  The CS pin is high by default and the
 * Arduino's SD library leaves CS high when the microSD card is not being used,
 * so most users will not need to worry about that. */
class AStar32U4PrimeButtonA : public Pushbutton
{
public:
    AStar32U4PrimeButtonA() : Pushbutton(A_STAR_32U4_PRIME_BUTTON_A)
    {
    }
};

/*! \brief Interfaces with button B on the A-Star 32U4 Prime.
 *
 * The pin used for button B is also used for the TX LED.
 *
 * This class temporarily disables USB interrupts because the Arduino core code
 * has USB interrupts enabled that sometimes write to the pin this button is on.
 *
 * This class temporarily sets the pin to be an input without a pull-up
 * resistor.  The pull-up resistor is not needed because of the resistors on the
 * board. */
class AStar32U4PrimeButtonB : public PushbuttonBase
{
public:
    virtual bool isPressed()
    {
        // These objects take care of disabling USB interrupts temporarily
        // and restoring the pin to its previous state at the end.
        USBPause usbPause;
        FastGPIO::PinLoan<A_STAR_32U4_PRIME_BUTTON_B> loan;

        FastGPIO::Pin<A_STAR_32U4_PRIME_BUTTON_B>::setInput();
        _delay_us(3);
        return !FastGPIO::Pin<A_STAR_32U4_PRIME_BUTTON_B>::isInputHigh();
    }
};

/*! \brief Interfaces with button C on the A-Star 32U4 Prime.
 *
 * The pin used for button C is also used for the RX LED.
 *
 * This class temporarily disables USB interrupts because the Arduino core code
 * has USB interrupts enabled that sometimes write to the pin this button is on.
 *
 * This class temporarily disables the AVR's hardware SPI module because it
 * might have been enabled by the Arduino's SD library, and the pin for button C
 * is the SPI SS line.  If it is an input and it reads low, the state of the SPI
 * module will be changed.
 *
 * This class temporarily sets the pin to be an input without a pull-up
 * resistor.  The pull-up resistor is not needed because of the resistors on the
 * board.
 */
class AStar32U4PrimeButtonC : public PushbuttonBase
{
public:
    virtual bool isPressed()
    {
        SPIPause spiPause;
        USBPause usbPause;
        FastGPIO::PinLoan<A_STAR_32U4_PRIME_BUTTON_C> loan;

        FastGPIO::Pin<A_STAR_32U4_PRIME_BUTTON_C>::setInput();
        _delay_us(3);
        return !FastGPIO::Pin<A_STAR_32U4_PRIME_BUTTON_C>::isInputHigh();
    }
};
