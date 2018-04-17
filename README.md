# Pololu A-Star Software and Drivers

Version: 4.0.2<br>
Release date: 2018-04-17<br>
[www.pololu.com](https://www.pololu.com/)

These files are the software and drivers for the Pololu
[A-Star 32U4 and A-Star 328PB boards][a-star], along with Pololu's
ATmega32U4-based robots ([Zumo 32U4][zumo], [Balboa 32U4][balboa], and
[Romi 32U4 Control Board][romi]).

For more information about A-Star boards and robots, see their user's guides:

- [A-Star 32U4 (Micro, Mini, Prime) user's guide][32u4-guide]
- [A-Star 32U4 Robot Controller user's guide][robot-controller-guide]
- [A-Star 328PB user's guide][328pb-guide]
- [Zumo 32U4 Robot user's guide][zumo-guide]
- [Balboa 32U4 Balancing Robot user's guide][balboa-guide]
- [Romi 32U4 Control Board user's guide][romi-guide]

These files are available on [GitHub](https://github.com/pololu/a-star).


## Arduino IDE integration

These files can be used to add A-Star and robot support to the Arduino IDE.
Entries for **Pololu A-Star Boards** will appear in the **Boards** menu
when you do this.

For most people, we recommend setting up A-Star support in the Arduino IDE by
installing our boards package through the Boards Manager. (These instructions
can also be found in the user's guide for each controller).

1.  In the Arduino IDE, open the **File** menu (Windows/Linux) or the
    **Arduino** menu (macOS) and select "Preferences".

2.  In the Preferences dialog, find the "Additional Boards Manager URLs" text
    box. Copy and paste the following URL into this box:

    **`https://files.pololu.com/arduino/package_pololu_index.json`**

    If there are already other URLs in the box, you can either add this one
    separated by a comma or click the button next to the box to open an input
    dialog where you can add the URL on a new line.

3.  Click the "OK" button to close the Preferences dialog.

4.  In the **Tools > Board** menu, select "Boards Manager..." (at the top of the
    menu).

5.  In the Boards Manager dialog, search for "Pololu A-Star Boards".

6.  Select the "Pololu A-Star Boards" entry in the list, and click the
    "Install" button.

For additional information, including instructions for uploading a sketch and
troubleshooting, refer to the user's guide for your controller.

### Manual installation

To manually add A-Star and robot support to the Arduino IDE, follow these steps.

1.  Download [the latest release archive from GitHub][releases] and decompress
    it.

2.  Rename the directory "a-star-xxxx" (which includes this README,
    platform.txt, boards.txt, and other files) to "avr".

3.  Locate your Arduino sketchbook directory. You can view your sketchbook
    location by opening the **File** menu and selecting **Preferences** in the
    Arduino IDE.

4.  Inside the Arduino sketchbook folder, add a folder named "hardware" if it
    does not already exist.

5.  Inside the "hardware" folder, add a folder named "pololu" if it does not
    already exist.

6.  Move the "avr" folder into the "pololu" folder.

7.  Restart the Arduino IDE.

8.  In the **Boards** menu, you should now see entries for the Pololu A-Star
    boards.

If you do not see these entries in the "Boards" menu, make sure that the final
path to this README looks like this (where "Arduino" is your sketchbook
directory):

**`Arduino/hardware/pololu/avr/README.md`**


## ATmega328PB support in the Arduino IDE

These files have been tested with the Arduino IDE version 1.8.5.  Since that
version of the IDE does not have official ATmega328PB support, these files
configure the compiler to target the older ATmega328P, which is very similar to
the PB.  We added extra definitions so you can use all of the new features of
the ATmega328PB, while still being able to compile almost any code that worked
on the older ATmega328P.

Here are some details about what Arduino features work when programming the
A-Star 328PB in the Arduino IDE:

- The `Serial` and `Serial1` objects both work, providing access to UART0 and
  UART1, respectively.
- There is no library support for accessing the ATmega328PB's second I2C module
  (TWI1), or its second SPI module (SPI1).  However, you can access the
  registers for those new modules and define ISRs for them.
- `pinMode()`, `digitalRead()`, and `digitalWrite()` should work on every I/O
  pin.
- `analogRead()` should work on every analog pin (A0 through A7).
- `analogWrite()` should work on every pin with PWM.

The ATmega328PB has two new pins, PE0 and PE1, that have no equivalent on the
ATmega328P.  These pins do not yet have official pin numbers in the Arduino
environment, so if you need to use their pin numbers in your code, we recommend
using the constants `SDA1` (for PE0) and `SCL1` (for PE1) that are defined in
our header files.  For example:

```c++
digitalWrite(SDA1, HIGH);
```

## Bootloader

The "bootloader" directory contains the source code and compiled files for the
A-Star and Zumo bootloaders.  The A-Star 32U4 boards and ATmega32U4-based robots
use "caterina", while the A-Star 328PB boards use "optiboot".


## Drivers

The "drivers" directory contains the A-Star 32U4 drivers for Microsoft Windows.
To install the drivers, right-click on "a-star.inf" and select "Install".

## udev rules

The "udev-rules" directory contains a file named "a-star.rules" for Linux users.
If you copy this file to /etc/udev/rules.d/, it will tell ModemManager to not
try to access the virtual serial ports of the A-Star 32U4 and ATmega32U4-based
robots.  This is necessary on some systems in order to program these
devices.


## Library support

If you are programming an A-Star 32U4 or ATmega32U4-based robot with the Arduino
environment, you might also want to install the applicable Arduino libraries,
which are available in separate repositories:

- [AStar32U4 library][32u4-lib]
- [Zumo32U4 library][zumo-lib]
- [Balboa32U4 library][balboa-lib]
- [Romi32U4 library][romi-lib]

## Version history

- 4.0.2 (2018-04-17): Fixed an unquoted path in build flags that could cause an
                      error when compiling for the 328PB.
- 4.0.1 (2018-04-11): 328PB interrupt vectors should be linked into sketch more
                      reliably.
- 4.0.0 (2018-03-21): Moved selection of A-Star 328PB versions to custom menu.
- 3.1.0 (2018-02-20): Added support for A-Star 328PB.
- 3.0.1 (2016-12-01): Fixed A-Star 32U4 bootloader unlock/lock bits.
- 3.0.0 (2015-12-15): Restructured repository to work with the Arduino Boards
                      Manager.
- 2.0.0 (2015-09-01): Separated Arduino libraries into their own repositories
                      and removed them from this repository.

[a-star]: https://www.pololu.com/category/149/a-star-programmable-controllers
[zumo]: https://www.pololu.com/category/170/zumo-32u4-robot
[balboa]: https://www.pololu.com/product/3575
[romi]: https://www.pololu.com/product/3544

[32u4-guide]: https://www.pololu.com/docs/0J61
[robot-controller-guide]: https://www.pololu.com/docs/0J66
[328pb-guide]: https://www.pololu.com/docs/0J74
[zumo-guide]: https://www.pololu.com/docs/0J63
[balboa-guide]: https://www.pololu.com/docs/0J70
[romi-guide]: https://www.pololu.com/docs/0J69

[releases]: https://github.com/pololu/a-star/releases

[32u4-lib]: https://github.com/pololu/a-star-32u4-arduino-library
[zumo-lib]: https://github.com/pololu/zumo-32u4-arduino-library
[balboa-lib]: https://github.com/pololu/balboa-32u4-arduino-library
[romi-lib]: https://github.com/pololu/romi-32u4-arduino-library
