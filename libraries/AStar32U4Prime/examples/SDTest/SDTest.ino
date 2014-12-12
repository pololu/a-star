/* This is a test program for the A-Star 32U4 Prime that tests to
make sure the SD card, LCD, 3 user LEDs, and 3 buttons can all be
used at the same time even though they are sharing a lot of pins.

It looks for a file named "test.txt" in the top-level directory
on the SD card and opens it.  Every time one of the buttons is
pressed, it reads 512 more bytes from the SD card just to make
sure that any cached data in the SD libraries have been used up,
and then it reads 8 more bytes from the file.  Those 8 characters
are displayed on the LCD and printed to the serial monitor.

Note: This demo uses the standard A-Star 32U4 Prime LCD pins,
buzzer pin, button pins, microSD pins, and pin 4.  To avoid
damage or improper operation, if you have shields or other
electronics connected, make sure they do not use those pins in a
conflicting way.

== microSD card considerations ==

You will need to install a jumper between GND and CS to enable
the microSD card.

(You will also need to have a version of the A-Star 32U4 with a
microSD card socket and you will need to insert a formatted
microSD card into the socket.)

Note: While the GND/CS jumper is installed, button A will not
work.

Note: If the GND/CS jumper is installed and the microSD card is
not inserted, the state of the DO signal from the microSD card
will be undefined.  This could waste power and might also cause
this program to detect spurious presses on button A.

To avoid these issues, you can connect CS to pin 4 using a
male-female jumper wire instead of connecting CS to GND.  This
program drives pin 4 low whenever the microSD card is accessed
and drives it high the rest of the time, allowing button A to
work properly. */

#include <AStar32U4Prime.h>
#include <SPI.h>
#include <SD.h>

AStar32U4PrimeLCD lcd;
AStar32U4PrimeBuzzer buzzer;
AStar32U4PrimeButtonA buttonA;
AStar32U4PrimeButtonB buttonB;
AStar32U4PrimeButtonC buttonC;

const uint8_t chipSelect = 4;

void setup()
{
  char lastButton = ' ';

  // Initialize the SD card.
  lcd.clear();
  lcd.print("Init...");
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    buzzer.playNote(NOTE_C(2), 100, 15);
    lcd.clear();
    lcd.print("Card err");
    while(1){}  // done
  }

  // Open the file.
  lcd.clear();
  lcd.print("Open...");
  Serial.println("Opening file...");
  File file = SD.open("test.txt");
  if (!file)
  {
    Serial.println("error opening test.txt");
    buzzer.playNote(NOTE_C(2), 100, 15);
    lcd.clear();
    lcd.print("File err");
    while(1){}  // done
  }

  // Start a loop where we will read data from the file, keeping
  // track of what line number we are on.
  uint32_t lineNumber = 1;
  while (true)
  {
    // Read 8 bytes from the file and store it in "line".
    char line[8];
    for(uint8_t i = 0; i < sizeof(line); i++)
    {
      if (!file.available()) { goto eof; }
      char x = file.read();
      if (x == '\n') { lineNumber++; }
      line[i] = x;
    }

    // Replace unprintable characters with spaces.  Some
    // characters will still get printed incorrectly on the LCD,
    // but should look correct in the serial monitor.
    for(uint8_t i = 0; i < sizeof(line); i++)
    {
      if (!isprint(line[i]))
      {
        line[i] = ' ';
      }
    }

    // Display the line number, position, and eight characters
    // from the file on the LCD.
    lcd.clear();
    lcd.print(lineNumber);
    lcd.print(' ');
    lcd.print(file.position());
    lcd.gotoXY(0, 1);
    lcd.write(line, 8);

    // Also print info to the serial monitor.
    Serial.print(lastButton);
    Serial.print(' ' );
    Serial.print(lineNumber);
    Serial.print(' ');
    Serial.print(file.position());
    Serial.print(' ');
    Serial.write(line, 8);
    Serial.println();

    // Wait for a button press while blinking all the LEDs.
    while(1)
    {
      ledRed(millis() >> 10 & 1);
      ledYellow(millis() >> 9 & 1);
      ledGreen(millis() >> 8 & 1);

      // Whenever a button is pressed, we play a distinctive note
      // for that button, record the button press, and break out
      // of this loop.

      if (buttonA.getSingleDebouncedPress())
      {
        buzzer.playNote(NOTE_G(3), 100, 15);
        lastButton = 'A';
        break;
      }

      if (buttonB.getSingleDebouncedPress())
      {
        buzzer.playNote(NOTE_G(4), 100, 15);
        lastButton = 'B';
        break;
      }

      if (buttonC.getSingleDebouncedPress())
      {
        buzzer.playNote(NOTE_G(5), 100, 15);
        lastButton = 'C';
        break;
      }
    }

    // Read 512 bytes from the file to clear out any caches in
    // the Arduino SD library.
    for (uint16_t i = 0; i < 512; i++)
    {
      if (!file.available()) { goto eof; }
      char x = file.read();
      if (x == '\n') { lineNumber++; }
    }
  }

  eof:  // We reached the end of the file.

  file.close();

  buzzer.playNote(NOTE_G(2), 100, 15);
  lcd.clear();
  lcd.print("EOF");
  Serial.println("EOF");
}

void loop()
{
}
