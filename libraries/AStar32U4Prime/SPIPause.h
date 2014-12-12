// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/*! \file SPIPause.h */

#pragma once

#include <avr/io.h>

/*! This class disables the AVR's hardware SPI module in its constructor when it
 *  is created and restores it to its previous state in its destructor when it
 *  is destroyed.
 *
 * It can be useful if you want to use one of the SPI pins (MOSI, MISO, SCK, or
 * SS) for some other purpose temporarily. */
class SPIPause
{
    /// The saved value of the SPCR register.
    uint8_t savedSPCR;

public:

    SPIPause()
    {
        savedSPCR = SPCR;
        SPCR &= ~(1 << SPE);
    }

    ~SPIPause()
    {
        SPCR = savedSPCR;
    }

};
