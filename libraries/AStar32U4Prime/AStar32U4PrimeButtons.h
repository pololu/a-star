/** \file AStar32U4PrimeButtons.h */

#pragma once

#include <Pushbutton.h>
#include <FastGPIO.h>
#include <USBPause.h>
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

/*! \brief Interfaces with button A on the A-Star 32U4 Prime. */
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
 * This class temporarily disables USB interrupts in order to get a reliable
 * reading of the button's state.  It also restores the pin to its previous
 * state after it is done so that it can still be used to control the LED. */
class AStar32U4PrimeButtonB : public PushbuttonBase
{
public:
    virtual bool isPressed()
    {
        // These objects take care of disabling USB interrupts temporarily
        // and restoring the pin to its previous state at the end.
        USBPause usbPause;
        FastGPIO::PinLoan<A_STAR_32U4_PRIME_BUTTON_B> loan;

        FastGPIO::Pin<A_STAR_32U4_PRIME_BUTTON_B>::setInputPulledUp();
        _delay_us(3);
        return !FastGPIO::Pin<A_STAR_32U4_PRIME_BUTTON_B>::isInputHigh();
    }
};

/*! \brief Interfaces with button C on the A-Star 32U4 Prime.
 *
 * The pin used for button C is also used for the RX LED.
 *
 * This class temporarily disables USB interrupts in order to get a reliable
 * reading of the button's state.  It also restores the pin to its previous
 * state after it is done so that it can still be used to control the LED. */
class AStar32U4PrimeButtonC : public PushbuttonBase
{
public:
    virtual bool isPressed()
    {
        // These objects take care of disabling USB interrupts temporarily
        // and restoring the pin to its previous state at the end.
        USBPause usbPause;
        FastGPIO::PinLoan<A_STAR_32U4_PRIME_BUTTON_C> loan;

        FastGPIO::Pin<A_STAR_32U4_PRIME_BUTTON_C>::setInputPulledUp();
        _delay_us(3);
        return !FastGPIO::Pin<A_STAR_32U4_PRIME_BUTTON_C>::isInputHigh();
    }
};
