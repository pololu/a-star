# AStar32U4Prime library

Version: 1.1.2<br/>
Release date: 2015 May 06<br/>
[www.pololu.com](http://www.pololu.com/)

## Summary

This is a C++ library for the Arduino IDE that helps access the on-board hardware of the [A-Star 32U4 Prime](http://www.pololu.com/category/165/a-star-32u4-prime), which is a family of programmable controllers from Pololu based on the ATmega32U4.  You can program the A-Star 32U4 Prime directly from the Arduino IDE without using this library, but this library makes it easy to:

* display information on the LCD
* play sounds and music on the buzzer
* read the battery voltage level
* control the three user LEDs
* use the three user pushbuttons

## Installing the library

You can download this library from the [Pololu A-Star 32U4 User's Guide](http://www.pololu.com/docs/0J61) or from the [a-star repository on GitHub](https://github.com/pololu/a-star).  Extract the files from the downloaded ZIP file and find the "AStar32U4Prime" directory, which is inside the "libraries" folder.  Copy the "AStar32U4Prime" folder into the "libraries" subdirectory inside your Arduino sketchbook directory.  You can see the sketchbook location in the Arduino IDE Preferences dialog, which is available from the File menu.  For a typical user, the sketchbook location will be a folder named Arduino inside the Documents folder.  For a typical user running a recent version of Windows, the "AStar32U4Prime" folder should be installed in this location:

`C:\Users\<username>\Documents\Arduino\libraries\AStar32U4Prime`

After installing the library, restart the Arduino IDE.

## Examples

Several example sketches are available that show how to use the library.  You can access them from the Arduino IDE by opening the "File" menu, selecting "Examples", and then selecting "AStar32U4Prime".  If you cannot find these examples, the library was probably installed incorrectly and you should retry the installation instructions above.

## Classes and functions

The main classes and functions provided by the library are listed below:

* AStar32U4PrimeButtonA
* AStar32U4PrimeButtonB
* AStar32U4PrimeButtonC
* AStar32U4PrimeBuzzer
* AStar32U4PrimeLCD
* ledGreen()
* ledRed()
* ledYellow()
* readBatteryMillivoltsLV()
* readBatteryMillivoltsSV()
* usbPowerPresent()

## Component libraries

This library also includes copies of several other Arduino libraries inside it which are used to help implement the classes and functions above:

* [FastGPIO](https://github.com/pololu/fastgpio-arduino)
* [PololuBuzzer](https://github.com/pololu/pololu-buzzer-arduino)
* [PololuHD44780](https://github.com/pololu/pololu-hd44780-arduino)
* [Pushbutton](https://github.com/pololu/pushbutton-arduino)
* [USBPause](https://github.com/pololu/usb-pause-arduino)

The Pushbutton and FastGPIO libraries are generally useful and you might want to use them directly in your sketch.  You can use these libraries automatically without any extra installation steps and without needing to add any extra `#include` lines to your sketch.

You should avoid adding extra `#include` lines such as `#include <Pushbutton.h>` because then the Arduino IDE might try to use the standalone %Pushbutton library (if you previously installed it), and it would conflict with the copy of the Pushbutton code included in the AStar32U4Prime library.  The only `#include` line needed to access all features of this library is:

~~~{.cpp}
#include <AStar32U4Prime.h>
~~~

## Documentation

For complete documentation, see https://pololu.github.io/a-star-32u4-prime.  If you are already on that page, then click on the links in the "Classes and functions" section above.

## Version history

* 1.1.2 (2015 May 06): Updated FastGPIO to version 1.0.2.
* 1.1.1 (2015 Jan 06): Update to version 1.0.1 of the FastGPIO library, which has a minor change to fix some compiler warnings.
* 1.1.0 (2014 Dec 31): Added support for the A-Star 32U4 Prime SV.
* 1.0.0 (2014 Dec 11): Original release.