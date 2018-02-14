/*
 * This header file allows you to write code for the ATmega328PB on the
 * Pololu A-Star 328PB even if your avr-gcc toolchain does not support it.
 *
 * Your toolchain should be configured to compile for the ATmega328P.
 *
 * To use new interrupt vectors, you will need to use new_vectors_328pb.h too.
 */

#include <avr/io.h>

#ifndef _AVR_ATMEGA328PB_H_INCLUDED
#define _AVR_ATMEGA328PB_H_INCLUDED

#define PINE  _SFR_IO8(0x0C)
#define PINE3 3
#define PINE2 2
#define PINE1 1
#define PINE0 0

#define DDRE  _SFR_IO8(0x0D)
#define DDRE3 3
#define DDE3  3
#define DDRE2 2
#define DDE2  2
#define DDRE1 1
#define DDE1  1
#define DDRE0 0
#define DDE0  0

#define PORTE  _SFR_IO8(0x0E)
#define PORTE3 3
#define PORTE2 2
#define PORTE1 1
#define PORTE0 0

#define TIFR3 _SFR_IO8(0x18)
#define ICF3  5
#define OCF3B 2
#define OCF3A 1
#define TOV3  0

#define TIFR4 _SFR_IO8(0x19)
#define ICF4  5
#define OCF4B 2
#define OCF4A 1
#define TOV4  0

#define PCIF3 3

// The ATmega328P's SPDR0 bit conflicts with the ATmega328PB's SPDR0 register,
// undefine all the bits like that.
#undef SPDR0
#undef SPDR1
#undef SPDR2
#undef SPDR3
#undef SPDR4
#undef SPDR5
#undef SPDR6
#undef SPDR7

#define SPCR0    SPCR
#define SPSR0    SPSR
#define SPDR0    SPDR

#define XFDCSR   _SFR_MEM8(0x62)
#define XFDIF    1
#define XFDIE    0

#define PRR0     PRR
#define PRTWI0   PRTWI
#define PRUSART1 4
#define PRSPI0   PRSPI

#define __AVR_HAVE_PRR0 0xFF
#define __AVR_HAVE_PRR0_PRADC
#define __AVR_HAVE_PRR0_PRUSART0
#define __AVR_HAVE_PRR0_PRSPI0
#define __AVR_HAVE_PRR0_PRTIM1
#define __AVR_HAVE_PRR0_PRUSART1
#define __AVR_HAVE_PRR0_PRTIM0
#define __AVR_HAVE_PRR0_PRTIM2
#define __AVR_HAVE_PRR0_PRTWI0

#define PRR1    _SFR_MEM8(0x65)
#define PRTWI1  5
#define PRPTC   4
#define PRTIM4  3
#define PRSPI1  2
#define PRTIM3  0

#define __AVR_HAVE_PRR1 0x3D
#define __AVR_HAVE_PRR1_PRTWI1
#define __AVR_HAVE_PRR1_PRPTC
#define __AVR_HAVE_PRR1_PRTIM4
#define __AVR_HAVE_PRR1_PRSPI1
#define __AVR_HAVE_PRR1_PRTIM3

#define OSCCAL7 7
#define OSCCAL6 6
#define OSCCAL5 5
#define OSCCAL4 4
#define OSCCAL3 3
#define OSCCAL2 2
#define OSCCAL1 1
#define OSCCAL0 0

#define PCIE3   3

#define TIMSK3  _SFR_MEM8(0x71)
#define ICIE3   5
#define OCIE3B  2
#define OCIE3A  1
#define TOIE3   0

#define TIMSK4  _SFR_MEM8(0x72)
#define ICIE4   5
#define OCIE4B  2
#define OCIE4A  1
#define TOIE4   0

#define PCMSK3  _SFR_MEM8(0x73)
#define PCINT27 3
#define PCINT26 2
#define PCINT25 1
#define PCINT24 0

#define TCCR3A  _SFR_MEM8(0x90)
#define COM3A1  7
#define COM3A0  6
#define COM3B1  5
#define COM3B0  4
#define WGM31   1
#define WGM30   0

#define TCCR3B  _SFR_MEM8(0x91)
#define ICNC3   7
#define ICES3   6
#define WGM33   4
#define WGM32   3
#define CS32    2
#define CS31    1
#define CS30    0

#define TCCR3C  _SFR_MEM8(0x92)
#define FOC3A   7
#define FOC3B   6

#define TCNT3   _SFR_MEM16(0x94)
#define TCNT3L  _SFR_MEM8(0x94)
#define TCNT3H  _SFR_MEM8(0x95)

#define ICR3    _SFR_MEM16(0x96)
#define ICR3L   _SFR_MEM8(0x96)
#define ICR3H   _SFR_MEM8(0x97)

#define OCR3A   _SFR_MEM16(0x98)
#define OCR3AL  _SFR_MEM8(0x98)
#define OCR3AH  _SFR_MEM8(0x99)

#define OCR3B   _SFR_MEM16(0x9A)
#define OCR3BL  _SFR_MEM8(0x9A)
#define OCR3BH  _SFR_MEM8(0x9B)

#define TCCR4A  _SFR_MEM8(0xA0)
#define COM4A1  7
#define COM4A0  6
#define COM4B1  5
#define COM4B0  4
#define WGM41   1
#define WGM40   0

#define TCCR4B  _SFR_MEM8(0xA1)
#define ICNC4   7
#define ICES4   6
#define WGM43   4
#define WGM42   3
#define CS42    2
#define CS41    1
#define CS40    0

#define TCCR4C  _SFR_MEM8(0xA2)
#define FOC4A   7
#define FOC4B   6

#define TCNT4   _SFR_MEM16(0xA4)
#define TCNT4L  _SFR_MEM8(0xA4)
#define TCNT4H  _SFR_MEM8(0xA5)

#define ICR4    _SFR_MEM16(0xA6)
#define ICR4L   _SFR_MEM8(0xA6)
#define ICR4H   _SFR_MEM8(0xA7)

#define OCR4A   _SFR_MEM16(0xA8)
#define OCR4AL  _SFR_MEM8(0xA8)
#define OCR4AH  _SFR_MEM8(0xA9)

#define OCR4B   _SFR_MEM16(0xAA)
#define OCR4BL  _SFR_MEM8(0xAA)
#define OCR4BH  _SFR_MEM8(0xAB)

#define SPCR1   _SFR_MEM8(0xAC)
#define SPIE1   7
#define SPE1    6
#define DORD1   5
#define MSTR1   4
#define CPOL1   3
#define CPHA1   2
#define SPR11   1
#define SPR10   0

#define SPSR1   _SFR_MEM8(0xAD)
#define SPIF1   7
#define WCOL1   6
#define SPI2X1  0

#define SPDR1   _SFR_MEM8(0xAE)

// The ATmega328P's TWBR0 bit conflicts with the ATmega328PB's TWBR0 register,
// undefine all the bits like that.
#undef TWBR0
#undef TWBR1
#undef TWBR2
#undef TWBR3
#undef TWBR4
#undef TWBR5
#undef TWBR6
#undef TWBR7

#define TWBR0   TWBR
#define TWSR0   TWSR
#define TWAR0   TWAR
#define TWDR0   TWDR
#define TWCR0   TWCR
#define TWAMR0  TWAMR

#define UCSR1A  _SFR_MEM8(0xC8)
#define RXC1    7
#define TXC1    6
#define UDRE1   5
#define FE1     4
#define DOR1    3
#define UPE1    2
#define U2X1    1
#define MPCM1   0

#define UCSR1B  _SFR_MEM8(0xC9)
#define RXCIE1  7
#define TXCIE1  6
#define UDRIE1  5
#define RXEN1   4
#define TXEN1   3
#define UCSZ12  2
#define RXB81   1
#define TXB81   0

#define UCSR1C  _SFR_MEM8(0xCA)
#define UMSEL11 7
#define UMSEL10 6
#define UPM11   5
#define UPM10   4
#define USBS1   3
#define UCSZ11  2
#define UCSZ10  1
#define UCPOL1  0

#define UBRR1   _SFR_MEM16(0xCC)
#define UBRR1L  _SFR_MEM8(0xCC)
#define UBRR1H  _SFR_MEM8(0xCD)

// The datasheet says UDR1 is at 0xC7 but that is wrong.
#define UDR1    _SFR_MEM8(0xCE)

#define TWBR1   _SFR_MEM8(0xD8)

#define TWSR1   _SFR_MEM8(0xD9)

#define TWAR1   _SFR_MEM8(0xDA)

#define TWDR1   _SFR_MEM8(0xDB)

#define TWCR1   _SFR_MEM8(0xDC)

#define TWAMR1  _SFR_MEM8(0xDD)

#define SPI0_STC_vect          SPI_STC_vect
#define SPI0_STC_vect_num      SPI_STC_vect_num

#define USART0_RX_vect         USART_RX_vect
#define USART0_RX_vect_num     USART_RX_vect_num

#define USART0_UDRE_vect       USART_UDRE_vect
#define USART0_UDRE_vect_num   USART_UDRE_vect_num

#define USART0_TX_vect         USART_TX_vect
#define USART0_TX_vect_num     USART_TX_vect_num

#define TWI0_vect              TWI_vect
#define TWI0_vect_num          TWI_vect_num

#define USART_START_vect       _VECTOR(26)
#define USART_START_vect_num   26
#define USART0_START_vect      USART_START_vect
#define USART0_START_vect_num  USART_START_vect_num

#define PCINT3_vect            _VECTOR(27)
#define PCINT3_vect_num        27

#define USART1_RX_vect         _VECTOR(28)
#define USART1_RX_vect_num     28

#define USART1_UDRE_vect       _VECTOR(29)
#define USART1_UDRE_vect_num   29

#define USART1_TX_vect         _VECTOR(30)
#define USART1_TX_vect_num     30

#define USART1_START_vect      _VECTOR(31)
#define USART1_START_vect_num  31

#define TIMER3_CAPT_vect       _VECTOR(32)
#define TIMER3_CAPT_vect_num   32

#define TIMER3_COMPA_vect      _VECTOR(33)
#define TIMER3_COMPA_vect_num  33

#define TIMER3_COMPB_vect      _VECTOR(34)
#define TIMER3_COMPB_vect_num  34

#define TIMER3_OVF_vect        _VECTOR(35)
#define TIMER3_OVF_vect_num    35

#define CFD_vect               _VECTOR(36)
#define CFD_vect_num           36

#define PTC_EOC_vect           _VECTOR(37)
#define PTC_EOC_vect_num       37

#define PTC_WCOMP_vect         _VECTOR(38)
#define PTC_WCOMP_vect_num     38

#define SPI1_STC_vect          _VECTOR(39)
#define SPI1_STC_vect_num      39

#define TWI1_vect              _VECTOR(40)
#define TWI1_vect_num          40

#define TIMER4_CAPT_vect       _VECTOR(41)
#define TIMER4_CAPT_vect_num   41

#define TIMER4_COMPA_vect      _VECTOR(42)
#define TIMER4_COMPA_vect_num  42

#define TIMER4_COMPB_vect      _VECTOR(43)
#define TIMER4_COMPB_vect_num  43

#define TIMER4_OVF_vect        _VECTOR(44)
#define TIMER4_OVF_vect_num    44

#undef _VECTORS_SIZE
#define _VECTORS_SIZE 180

#undef SIGNATURE_2
#define SIGNATURE_2 0x16

#endif   /* #ifdef _AVR_ATMEGA328PB_H_INCLUDED */
