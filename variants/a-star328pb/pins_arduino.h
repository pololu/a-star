/* Modified by Pololu to support the ATmega328PB on our
 * A-Star 328PB boards. */

/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS            24
#define NUM_ANALOG_INPUTS           8
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 14 : -1)

#define digitalPinHasPWM(p)         ((p) == 0 || (p) == 1 || (p) == 2 || (p) == 3 || (p) == 5 || (p) == 6 || (p) == 9 || (p) == 10 || (p) == 11)

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (11)
#define PIN_SPI_MISO  (12)
#define PIN_SPI_SCK   (13)

#define PIN_SPI_SS0   (10)
#define PIN_SPI_MOSI0 (11)
#define PIN_SPI_MISO0 (12)
#define PIN_SPI_SCK0  (13)

#define PIN_SPI_SS1   (20)
#define PIN_SPI_MOSI1 (21)
#define PIN_SPI_MISO1 (14)
#define PIN_SPI_SCK1  (15)

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

static const uint8_t SS0 = PIN_SPI_SS0;
static const uint8_t MOSI0 = PIN_SPI_MOSI0;
static const uint8_t MISO0 = PIN_SPI_MISO0;
static const uint8_t SCK0 = PIN_SPI_SCK0;

static const uint8_t SS1 = PIN_SPI_SS1;
static const uint8_t MOSI1 = PIN_SPI_MOSI1;
static const uint8_t MISO1 = PIN_SPI_MISO1;
static const uint8_t SCK1 = PIN_SPI_SCK1;

#define PIN_WIRE_SDA (18)
#define PIN_WIRE_SCL (19)

#define PIN_WIRE_SDA0 (18)
#define PIN_WIRE_SCL0 (19)

#define PIN_WIRE_SDA1 (22)
#define PIN_WIRE_SCL1 (23)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

static const uint8_t SDA0 = PIN_WIRE_SDA0;
static const uint8_t SCL0 = PIN_WIRE_SCL0;

static const uint8_t SDA1 = PIN_WIRE_SDA1;
static const uint8_t SCL1 = PIN_WIRE_SCL1;

#define LED_BUILTIN 13

#define PIN_A0   (14)
#define PIN_A1   (15)
#define PIN_A2   (16)
#define PIN_A3   (17)
#define PIN_A4   (18)
#define PIN_A5   (19)
#define PIN_A6   (20)
#define PIN_A7   (21)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 23) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : (((p) <= 19) ? 1 : 3)))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 19) ? (&PCMSK1) : (((p) <= 23) ? (&PCMSK3) : (uint8_t *)0))))
#define digitalPinToPCMSKbit(p) (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : (((p) <= 19) ? ((p) - 14) : (((p) <= 21) ? ((p) - 18) : ((p) - 22)))))

#define digitalPinToInterrupt(p)  ((p) == 2 ? 0 : ((p) == 3 ? 1 : NOT_AN_INTERRUPT))

#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = {
  NOT_A_PORT,
  NOT_A_PORT,
  (uint16_t) &DDRB,
  (uint16_t) &DDRC,
  (uint16_t) &DDRD,
  (uint16_t) &DDRE,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
  NOT_A_PORT,
  NOT_A_PORT,
  (uint16_t) &PORTB,
  (uint16_t) &PORTC,
  (uint16_t) &PORTD,
  (uint16_t) &PORTE,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
  NOT_A_PORT,
  NOT_A_PORT,
  (uint16_t) &PINB,
  (uint16_t) &PINC,
  (uint16_t) &PIND,
  (uint16_t) &PINE,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
  PD, /* 0 */
  PD,
  PD,
  PD,
  PD,
  PD,
  PD,
  PD,
  PB, /* 8 */
  PB,
  PB,
  PB,
  PB,
  PB,
  PC, /* 14 */
  PC,
  PC,
  PC,
  PC,
  PC,
  PE, /* 20 */
  PE,
  PE,
  PE,
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
  _BV(0), /* 0, port D */
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(6),
  _BV(7),
  _BV(0), /* 8, port B */
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(0), /* 14, port C */
  _BV(1),
  _BV(2),
  _BV(3),
  _BV(4),
  _BV(5),
  _BV(2), /* 20, port E */
  _BV(3),
  _BV(0),
  _BV(1),
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
  TIMER3A,      /* 0 - port D */
  TIMER4A,
  TIMER3B,      /* Note: We could choose TIMER4B instead. */
  TIMER2B,
  NOT_ON_TIMER,
  TIMER0B,
  TIMER0A,
  NOT_ON_TIMER,
  NOT_ON_TIMER, /* 8 - port B */
  TIMER1A,
  TIMER1B,
  TIMER2A,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER, /* 14 - port C */
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER, /* 20 - port E */
  NOT_ON_TIMER,
  NOT_ON_TIMER,
  NOT_ON_TIMER,
};

#endif

#define SERIAL_PORT_MONITOR Serial
#define SERIAL_PORT_HARDWARE Serial
#define SERIAL_PORT_HARDWARE_OPEN Serial1

inline void analogWrite328PB(uint8_t pin, int val)
{
  if (pin == 2)
  {
    if (val)
    {
      // To make analogWrite work on pin 2, we must configure the output compare
      // modulator (OCM) to combine the OC3B and OC4B signals with an OR gate
      // instead of AND.
      PORTD |= (1 << 2);
    }
    else
    {
      // Avoid a glitch when setting the value to 0.
      PORTD &= ~(1 << 2);
    }
  }
  analogWrite(pin, val);
}

// This is fragile: when compiling C code, leave analogWrite alone so that
// wiring_analog.c can define the analogWrite function as usual.  When compiling
// C++ code, define analogWrite as analogWrite328PB so that it works properly.
#ifdef __cplusplus
#define analogWrite analogWrite328PB
#endif

#endif
