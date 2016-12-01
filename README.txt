Pololu A-Star/Zumo 32U4 Software and Drivers

These files are the software and drivers for the Pololu A-Star 32U4 boards,
which are a family of programmable modules featuring Atmel's ATmega32U4
microcontroller. They are also used for the A-Star-compatible Zumo 32U4 robot.

For more information about A-Star boards, see their user's guides:
A-Star 32U4 (Micro, Mini, Prime): http://www.pololu.com/docs/0J61
A-Star 32U4 Robot Controller: https://www.pololu.com/docs/0J66
Zumo 32U4 Robot: https://www.pololu.com/docs/0J63

These files are available on GitHub:
https://github.com/pololu/a-star

For programming an A-Star 32U4 or Zumo 32U4 with the Arduino environment, you
might also want to install the applicable Arduino library:
https://github.com/pololu/a-star-32u4-arduino-library
https://github.com/pololu/zumo-32u4-arduino-library


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
the Arduino IDE.  In the "Boards" menu, you should now see an entry for "Pololu
A-Star 32U4".

If you do not see the entry in the "Boards" menu, make sure that the final path
to this README looks like this:

    Arduino/hardware/pololu/avr/README.txt


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
