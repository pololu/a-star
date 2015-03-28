Pololu A-Star Software and Drivers

These files are the software and drivers for the Pololu A-Star 32U4 boards,
which are a family of programmable modules featuring Atmel's ATmega32U4
microcontroller.

For more information about the A-Star, see the user's guide:
http://www.pololu.com/docs/0J61

These files are available on GitHub:
https://github.com/pololu/a-star


== Arduino add-on ==

The "add-on" directory contains a folder named "pololu" which can be used to add
a "Pololu A-Star 32U4" entry to the "Board" menu in the Arduino IDE.  The add-on
supports the 1.0.x, 1.5.x, and 1.6.x, versions of the Arduino IDE.

To install the add-on, copy the "pololu" folder into the "hardware" subfolder of
the Arduino sketchbook location.  The Arduino sketchbook location is typically
in your Documents folder in a subfolder named "Arduino".  You can see the
sketchbook location in the Arduino IDE Preferences dialog, which is available
from the File menu.


== Bootloader ==

The "bootloader" directory contains the source code and compiled files for the
A-Star 32U4 Bootloader.


== Drivers ==

The "drivers" directory contains the A-Star drivers for Microsoft Windows.  To
install the drivers, right-click on "a-star.inf" and select "Install".


== udev rules ==

The "udev-rules" directory contains a file named "a-star.rules" for Linux users.
If you copy this file to /etc/udev/rules.d/, it will tell ModemManager to not
try to access the virtual serial ports of the A-Star.  This is necessary on some
systems in order to program the A-Star.


== AStar32U4Prime library ==

The "libraries" directory contains the AStar32U4Prime library, which can help
you write code that interfaces with on-board hardware on the A-Star 32U4 Prime.
For more information, see the library's README.md file.

== Zumo32U4 library ==

The "libraries" directory contains the Zumo32U4 library, which can help you
write code that interfaces with on-board hardware on the Zumo 32U4 robot.  For
more information, see the library's README.md file.
