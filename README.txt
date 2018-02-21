Pololu A-Star/Zumo Software and Drivers

These files are the software and drivers for the Pololu A-Star 32U4, Zumo 32U4,
and A-Star 328PB boards.

For more information about A-Star and Zumo boards, see their user's guides:

- A-Star 32U4 (Micro, Mini, Prime): http://www.pololu.com/docs/0J61
- A-Star 32U4 Robot Controller: https://www.pololu.com/docs/0J66
- Zumo 32U4 Robot: https://www.pololu.com/docs/0J63

These files are available on GitHub:

    https://github.com/pololu/a-star


== Arduino IDE integration ==

These files can be used to add A-Star and Zumo support to the Arduino IDE.  An
entry for the "Pololu A-Star 32U4" will appear in the "Boards" menu when you do
this.

To add A-Star and Zumo support to the Arduino IDE, download these files and
rename the directory that contains this README to "avr".  Next, locate your
Arduino sketchbook folder, which is typically in your Documents folder in a
subfolder named "Arduino".  You can see the sketchbook location in the Arduino
IDE preferences dialog, which is available from the File menu.  Inside the
Arduino sketchbook folder, add a folder named "hardware" if it does not already
exist.  Inside the "hardware" folder, add a folder named "pololu" if it does not
already exist.  Then move the "avr" folder (which includes this README,
platform.txt, boards.txt, and other files) into the "pololu" folder.  Restart
the Arduino IDE.  In the "Boards" menu, you should now see an entries for the
Pololu A-Star 32U4 and the variations of the Pololu A-Star 328PB.

If you do not see the entry in the "Boards" menu, make sure that the final path
to this README looks like this:

    Arduino/hardware/pololu/avr/README.txt

In the example above, Arduino is the sketchbook folder, which is typically
located in your Documents folder.


== ATmega328PB support in the Arduino IDE ==

These files have been tested with the Arduino IDE version 1.8.5.  Since that
version of the IDE does not have official ATmega328PB support, these files
configure the compiler to target the older ATmega328P, which is very similar to
the PB.  We added extra definitions so you can use all of the new features of
the ATmega328PB, while still being able to compile almost any code that worked
on the older ATmega328P.

Here are some details about what Arduino features work when programming the
A-Star 328PB in the Arduino IDE:

- The "Serial" and "Serial1" objects both work, providing access to UART0 and
  UART1, respectively.
- There is no library support for accessing the ATmega328PB's second I2C module
  (TWI1), or its second SPI module (SPI1).  However, you can access the registers
  for those new modules and define ISRs for them.
- pinMode, digitalRead, and digitalWrite should work on every I/O pin.
- analogRead should work on every analog pin (A0 through A7)
- analogWrite should work on every pin with PWM.

The ATmega328PB has two new two pins named SCL1 and SDA1 that were not present
on the ATmega328P.  These pins do not yet have official pin numbers in the
Arduino environment, so if you need to use their pin numbers in your code, we
recommend using the constants "SCL1" and "SDA1" that are defined in our header
files.  For example:

    digitalWrite(SDA1, HIGH);


== Bootloader ==

The "bootloader" directory contains the source code and compiled files for the
A-Star and Zumo bootloaders.  The A-Star 32U4 and Zumo 32U4 boards use
"caterina", while the A-Star 328PB boards use "optiboot".


== Drivers ==

The "drivers" directory contains the A-Star 32U4 drivers for Microsoft Windows.
To install the drivers, right-click on "a-star.inf" and select "Install".


== udev rules ==

The "udev-rules" directory contains a file named "a-star.rules" for Linux users.
If you copy this file to /etc/udev/rules.d/, it will tell ModemManager to not
try to access the virtual serial ports of the A-Star 32U4 and Zumo 32U4.  This
is necessary on some systems in order to program the A-Star 32U4 and Zumo 32U4.


== Library support ==

If you are programming an A-Star 32U4 or Zumo 32U4 with the Arduino environment,
you might also want to install the applicable Arduino libraries, which are
available in separate repositories:

    https://github.com/pololu/a-star-32u4-arduino-library

    https://github.com/pololu/zumo-32u4-arduino-library
