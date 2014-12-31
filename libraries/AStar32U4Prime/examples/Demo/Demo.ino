/* This demo program shows many features of the
A-Star 32U4 Prime.

It uses the buttons, LCD, and buzzer to provide a user interface.
It presents a menu to the user that lets the user select from
several different demos.

To use this demo program, you will need to have an LCD connected
to the A-Star 32U4 Prime.  If you cannot see any text on the LCD,
try rotating the contrast potentiometer.

Note: This demo uses the standard A-Star 32U4 Prime LCD pins,
buzzer pin, button pins, microSD pins, and pin 4. To avoid damage
or improper operation, if you have shields or other electronics
connected, make sure they do not use those pins in a conflicting
way.

== microSD card considerations ==

To use the microSD card portion of this program, you will need to
install a jumper between GND and CS.

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
demo drives pin 4 low whenever the microSD card is accessed and
drives it high the rest of the time, allowing button A to work
properly. */


/* This demo assumes you are using the A-Star 32U4 Prime LV (the
blue board).  If not, then comment out the line below. */
#define A_STAR_LV

// Assume this will run on the A-Star 32U4 Prime SV (the green
// board) if it is not running on the LV.
#ifndef A_STAR_LV
#define A_STAR_SV
#endif

// This demo drives pin 4 low whenver the SD card is being used.
const uint8_t chipSelect = 4;

#include <AStar32U4Prime.h>
#include <SPI.h>
#include <SD.h>

AStar32U4PrimeLCD lcd;
AStar32U4PrimeBuzzer buzzer;
AStar32U4PrimeButtonA buttonA;
AStar32U4PrimeButtonB buttonB;
AStar32U4PrimeButtonC buttonC;

class Menu
{
public:
  struct Item
  {
    const char * name;
    void (* action)();
  };

  Menu(Item * items, uint8_t itemCount)
  {
    this->items = items;
    this->itemCount = itemCount;
    lcdItemIndex = 0;
  }

  void lcdUpdate(uint8_t index)
  {
    lcd.clear();
    lcd.print(items[index].name);
    lcd.gotoXY(0, 1);
    lcd.print(F("\x7f" "A \xa5" "B C\x7e"));
  }

  void action(uint8_t index)
  {
    items[index].action();
  }

  // Prompts the user to choose one of the menu items,
  // then runs it, then returns.
  void select()
  {
    lcdUpdate(lcdItemIndex);

    while(1)
    {
      switch(buttonMonitor())
      {
      case 'A':
        // The A button was pressed so decrement the index.
        if (lcdItemIndex == 0)
        {
          lcdItemIndex = itemCount - 1;
        }
        else
        {
          lcdItemIndex--;
        }
        lcdUpdate(lcdItemIndex);
        break;

      case 'C':
        // The C button was pressed so increase the index.
        if (lcdItemIndex >= itemCount - 1)
        {
          lcdItemIndex = 0;
        }
        else
        {
          lcdItemIndex++;
        }
        lcdUpdate(lcdItemIndex);
        break;

      case 'B':
        // The B button was pressed so, run the item and return.
        action(lcdItemIndex);
        return;
      }
    }
  }

private:
  Item * items;
  uint8_t itemCount;
  uint8_t lcdItemIndex;
};


// A couple of simple tunes, stored in program space.
const char beepBrownout[] PROGMEM = "<c32<e32#<g32";
const char beepWelcome[] PROGMEM = ">g32>>c32";
const char beepThankYou[] PROGMEM = ">>c32>g32";
const char beepButtonA[] PROGMEM = "!c32";
const char beepButtonB[] PROGMEM = "!e32";
const char beepButtonC[] PROGMEM = "!g32";
const char beepTimerTick[] PROGMEM = "!v8>>c32";

// Custom characters for the LCD:

// This character is a musical note.
const char note[] PROGMEM = {
  0b00100,
  0b00110,
  0b00101,
  0b00101,
  0b00100,
  0b11100,
  0b11100,
  0b00000,
};

// This character is a back arrow.
const char backArrow[] PROGMEM = {
  0b00000,
  0b00010,
  0b00001,
  0b00101,
  0b01001,
  0b11110,
  0b01000,
  0b00100,
};

void loadCustomCharacters()
{
  // The LCD supports up to 8 custom characters.  Each character
  // has a number between 0 and 7.  We assign #6 to be the back
  // arrow, and #7 to be the musical note.
  lcd.loadCustomCharacter(backArrow, 6);
  lcd.loadCustomCharacter(note, 7);
}

// Clears the LCD and puts [back_arrow]B on the second line
// to indicate to the user that the B button goes back.
void displayBackArrow()
{
  lcd.clear();
  lcd.gotoXY(0,1);
  lcd.print(F("\6B"));
  lcd.gotoXY(0,0);
}

// Acts as a two-key keyboard.  You can press button A or button
// C to send the corresponding keys to the computer.  For more
// information, see the Keyboard example.
void keyboardDemo()
{
  displayBackArrow();
  lcd.print(F("Type A/C"));

  while(1)
  {
    if (buttonA.getSingleDebouncedPress())
    {
      // Button A was pressed.
      Keyboard.press('a');
      buzzer.playFromProgramSpace(beepButtonA);
    }
    if (!buttonA.isPressed())
    {
      Keyboard.release('a');
    }

    if (buttonC.getSingleDebouncedPress())
    {
      // Button C was pressed.
      Keyboard.press('c');
      buzzer.playFromProgramSpace(beepButtonC);
    }
    if (!buttonC.isPressed())
    {
      Keyboard.release('c');
    }

    if (buttonB.getSingleDebouncedPress())
    {
      // Button B was pressed, so quit.
      buzzer.playFromProgramSpace(beepButtonB);
      break;
    }
  }
}

// Blinks all three LEDs in sequence.
void ledDemo()
{
  displayBackArrow();

  uint8_t state = 3;
  static uint16_t lastUpdateTime = millis() - 2000;
  while(buttonMonitor() != 'B')
  {
    if ((uint16_t)(millis() - lastUpdateTime) >= 500)
    {
      lastUpdateTime = millis();
      state = state + 1;
      if (state >= 4) { state = 0; }

      switch(state)
      {
      case 0:
        buzzer.play("c32");
        lcd.gotoXY(0, 0);
        lcd.print("Red   ");
        ledRed(1);
        ledGreen(0);
        ledYellow(0);
        break;

      case 1:
        buzzer.play("e32");
        lcd.gotoXY(0, 0);
        lcd.print("Green");
        ledRed(0);
        ledGreen(1);
        ledYellow(0);
        break;

      case 2:
        buzzer.play("g32");
        lcd.gotoXY(0, 0);
        lcd.print("Yellow");
        ledRed(0);
        ledGreen(0);
        ledYellow(1);
        break;
      }
    }
  }

  ledRed(0);
  ledYellow(0);
  ledGreen(0);
}

const char fugue[] PROGMEM =
  "! T120O5L16agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8MS<b-d<b-d MLe-<ge-<g MSc<ac<a MLd<fd<f O5MSb-gb-g"
  "ML>c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe fO6dc#dfdc#<b c#4";

const char fugueTitle[] PROGMEM =
  "       \7 Fugue in D Minor - by J.S. Bach \7       ";

// Play a song on the buzzer and display its title.
void musicDemo()
{
  displayBackArrow();

  uint8_t fugueTitlePos = 0;
  uint16_t lastShiftTime = millis() - 2000;

  while(buttonMonitor() != 'B')
  {
    // Shift the song title to the left every 250 ms.
    if((uint16_t)(millis() - lastShiftTime) > 250)
    {
      lastShiftTime = millis();

      lcd.gotoXY(0, 0);
      for(uint8_t i = 0; i < 8; i++)
      {
        char c = pgm_read_byte(fugueTitle + fugueTitlePos + i);
        lcd.write(c);
      }
      fugueTitlePos++;

      if(fugueTitlePos + 8 >= sizeof(fugueTitle))
      {
        fugueTitlePos = 0;
      }
    }

    if(!buzzer.isPlaying())
    {
      buzzer.playFromProgramSpace(fugue);
    }
  }
}

// Display the the battery (VIN) voltage and indicate whether USB
// power is detected.
void powerDemo()
{
  uint16_t lastDisplayTime = millis() - 2000;
  while(buttonMonitor() != 'B')
  {
    if ((uint16_t)(millis() - lastDisplayTime) > 250)
    {
      bool usbPower = usbPowerPresent();

#if defined(A_STAR_LV)
      uint16_t batteryLevel = readBatteryMillivoltsLV();
#elif defined(A_STAR_SV)
      uint16_t batteryLevel = readBatteryMillivoltsSV();
#else
#error "Unknown board"
#endif

      lastDisplayTime = millis();
      lcd.clear();
      lcd.print(batteryLevel);
      lcd.print(F(" mV"));
      lcd.gotoXY(0, 1);
      lcd.print(F("\6B USB="));
      lcd.print(usbPower ? 'Y' : 'N');
    }
  }
}

Sd2Card card;
SdVolume volume;

// Displays the size of the main partition on the inserted SD
// card.  If this doesn't work, see the notes at the top.
void sdDemo()
{
  lcd.clear();

  lcd.clear();
  lcd.print(F("SD..."));

  if (!(card.init(SPI_HALF_SPEED, chipSelect)))
  {
    lcd.clear();
    lcd.print(F("No SD   "));
  }
  else
  {
    lcd.print('.');

    if (!volume.init(card))
    {
      lcd.clear();
      lcd.print(F("No volum"));
    }
    else
    {
      // We multiply the number of clusters times the number of
      // blocks in a cluster to get the number of blocks.  Each
      // block is 512 bytes and there are 1024*1024 bytes in a
      // megabyte.
      uint32_t size = (uint32_t)volume.clusterCount() *
        volume.blocksPerCluster() * 512 / 1024 / 1024;
      lcd.clear();
      lcd.print(size);
      lcd.print(F(" MB"));
    }
  }

  // We are done checking the SD card, so display the back arrow
  // and wait for the user to press B.
  lcd.gotoXY(0, 1);
  lcd.print(F("\6B"));
  while(buttonMonitor() != 'B');
}

// Receives characters from the serial monitor and prints them on
// the LCD.  Also sends button press notifications to the serial
// monitor.
void serialMonitorDemo()
{
  lcd.clear();
  lcd.print(F("Type"));
  lcd.gotoXY(0, 1);
  lcd.print(F("into"));
  delay(1000);

  lcd.clear();
  lcd.print(F("serial"));
  lcd.gotoXY(0, 1);
  lcd.print(F("monitor."));
  delay(1000);

  lcd.cursorBlinking();
  displayBackArrow();

  Serial.flush();

  uint8_t column = 0;
  bool quit = 0;

  while(!quit)
  {
    if (Serial.available())
    {
      // We received a character from the serial port.
      char c = Serial.read();

      // Show the character on the LCD.
      if (column >= 8)
      {
        // The first line has filled up, so reset the display.
        displayBackArrow();
        column = 0;
      }
      column++;
      lcd.write(c);

      // Write a message back to the serial monitor saying the
      // hex value of the character received.
      Serial.print("Received character 0x");
      Serial.println((uint8_t)c, HEX);
    }

    // Send a message if button A or button C is pressed.
    // Quit if button B is pressed.
    switch(buttonMonitor())
    {
    case 'A':
      Serial.println(F("Button A was pressed."));
      break;

    case 'C':
      Serial.println(F("Button C was pressed."));
      break;

    case 'B':
      quit = true;
      break;
    }
  }

  lcd.hideCursor();
}

Menu::Item mainMenuItems[] = {
  { "Keyboard", keyboardDemo },
  { "LEDs", ledDemo },
  { "Music", musicDemo },
  { "Power", powerDemo },
  { "SD card", sdDemo },
  { "Serial", serialMonitorDemo },
};
Menu mainMenu(mainMenuItems, 6);

// This function watches for button presses.  If a button is
// pressed, it beeps a corresponding beep and it returns 'A',
// 'B', or 'C' depending on what button was pressed.  If no
// button was pressed, it returns 0.  This function is meant to
// be called repeatedly in a loop.
char buttonMonitor()
{
  if (buttonA.getSingleDebouncedPress())
  {
    buzzer.playFromProgramSpace(beepButtonA);
    return 'A';
  }

  if (buttonB.getSingleDebouncedPress())
  {
    buzzer.playFromProgramSpace(beepButtonB);
    return 'B';
  }

  if (buttonC.getSingleDebouncedPress())
  {
    buzzer.playFromProgramSpace(beepButtonC);
    return 'C';
  }

  return 0;
}

void setup()
{
  loadCustomCharacters();

  // The brownout threshold on the A-Star 32U4 is 4.3 V.  If VCC
  // drops below this, a brownout reset will occur, preventing
  // the AVR from operating out of spec.
  //
  // Note: Brownout resets usually do not happen on the A-Star
  // 32U4 Prime LV because the voltage regulator goes straight
  // from 5 V to 0 V when VIN drops too low.
  //
  // The bootloader is
  // designed so that you can detect brownout resets from your
  // sketch using the following code:
  bool brownout = MCUSR >> BORF & 1;
  MCUSR = 0;

  if (brownout)
  {
    // The board was reset by a brownout reset
    // (VCC dropped below 4.3 V).
    // Play a special sound and display a note to the user.

    buzzer.playFromProgramSpace(beepBrownout);
    lcd.clear();
    lcd.print(F("Brownout"));
    lcd.gotoXY(0, 1);
    lcd.print(F(" reset! "));
    delay(1000);
  }
  else
  {
    buzzer.playFromProgramSpace(beepWelcome);
  }

  lcd.clear();
  lcd.print(F(" A-Star"));
  lcd.gotoXY(0, 1);
#if defined(A_STAR_LV)
  lcd.print(F("Prime LV"));
#elif defined(A_STAR_SV)
  lcd.print(F("Prime SV"));
#else
#error "Unknown board"
#endif

  delay(1000);

  lcd.clear();
  lcd.print(F("Demo"));
  lcd.gotoXY(0, 1);
  lcd.print(F("Program"));
  delay(1000);

  lcd.clear();
  lcd.print(F("Use B to"));
  lcd.gotoXY(0, 1);
  lcd.print(F("select."));
  delay(1000);

  lcd.clear();
  lcd.print(F("Press B"));
  lcd.gotoXY(0, 1);
  lcd.print(F("-try it!"));

  while(buttonMonitor() != 'B'){}

  buzzer.playFromProgramSpace(beepThankYou);
  lcd.clear();
  lcd.print(F(" Thank"));
  lcd.gotoXY(0, 1);
  lcd.print(F("  you!"));
  delay(1000);
}

// This function prompts the user to choose something from the
// main menu, runs their selection, and then returns.
void mainMenuSelect()
{
  lcd.clear();
  lcd.print(F("  Main"));
  lcd.gotoXY(0, 1);
  lcd.print(F("  Menu"));
  delay(1000);
  mainMenu.select();
}

void loop()
{
  mainMenuSelect();
}
