/* This demo program shows many features of the
A-Star 32U4 Prime.

It uses the buttons, LCD, and buzzer to provide a user interface.
It presents a menu to the user that lets the user select from
several different demos. */

// The line below chooses what pin we will use to control the SD
// card's chip select (CS) signal in the SD card demo.  This pin
// needs to be connected to the CS input of the SD card or the SD
// card demo will not work.  It is not connected by default.
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
    lcd.gotoLine(1);
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
const char back_arrow[] PROGMEM = {
  0b00000,
  0b00010,
  0b00001,
  0b00101,
  0b01001,
  0b11110,
  0b01000,
  0b00100,
};

// Clears the LCD and puts [back_arrow]B on the second line
// to indicate to the user that the B button goes back.
void displayBackArrow()
{
  lcd.clear();
  lcd.gotoXY(0,1);
  lcd.print(F("\6B"));
  lcd.gotoXY(0,0);
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
      uint16_t batteryLevel = readBatteryMillivolts();

      lastDisplayTime = millis();
      lcd.clear();
      lcd.print(F("B="));
      lcd.print(batteryLevel);
      lcd.print(F("mV"));
      lcd.gotoXY(0, 1);
      lcd.print(F("\6B USB="));
      lcd.print(usbPower ? 'Y' : 'N');
    }
  }
}

Sd2Card card;
SdVolume volume;

// Displays the size of the main partition on the inserted SD
// card.  If this doesn't work, see the note about the chipSelect
// variable above.
void sdDemo()
{
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
      // We multiply the number of clusters times the number of blocks
      // in a cluster to get the number of blocks.  Each block is 512
      // bytes and there are 1024*1024 bytes in a megabyte.
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

// The timer demo turns the board into a stopwatch.
// Press the C button to start and stop the stopwatch.
// Press the A button to reset it.
void timerDemo()
{
  displayBackArrow();

  while(1)
  {
    static int32_t elapsedTime = 0;
    static int32_t lastRead = 0;
    static bool isTicking = 0;
    static char lastSeconds = 0;

    int32_t currentTime = millis();
    if(isTicking)
    {
      elapsedTime += currentTime - lastRead;
    }
    lastRead = currentTime;

    if (buttonA.getSingleDebouncedPress())
    {
      // Button A was pressed, so reset timer.
      isTicking = 0;
      elapsedTime = 0;
      buzzer.playFromProgramSpace(beepButtonA);
    }

    if (buttonC.getSingleDebouncedPress())
    {
      // Button C was pressed, so start/stop timer.
      isTicking = !isTicking;
      buzzer.playFromProgramSpace(beepButtonC);
    }

    // Update the LCD constantly.
    lcd.gotoXY(0, 0);
    lcd.print((elapsedTime/1000/60/10)%10);  // tens of minutes
    lcd.print((elapsedTime/1000/60)%10);  // minutes
    lcd.print(':');
    lcd.print((elapsedTime/1000)%60/10);  // tens of seconds
    uint8_t seconds = ((elapsedTime/1000)%60)%10;
    lcd.print(seconds);  // seconds
    lcd.print('.');
    lcd.print((elapsedTime/100)%10);  // tenths of seconds
    lcd.print((elapsedTime/10)%10);  // hundredths of seconds

    // Beep every second.
    if(seconds != lastSeconds && elapsedTime != 0 && !buzzer.isPlaying())
    {
      buzzer.playFromProgramSpace(beepTimerTick);
    }
    lastSeconds = seconds;

    if (buttonB.getSingleDebouncedPress())
    {
      // Button B was pressed, so play its sound and return.
      buzzer.playFromProgramSpace(beepButtonB);
      break;
    }
  }
}

Menu::Item mainMenuItems[] = {
  { "LEDs", ledDemo },
  { "Music", musicDemo },
  { "Power", powerDemo },
  { "SD card", sdDemo },
  { "Timer", timerDemo },
};
Menu mainMenu(mainMenuItems, 5);

void loadCustomCharacters()
{
  // The LCD supports up to 8 custom characters.  Each character
  // has a number between 0 and 7.  We assign #6 to be the back
  // arrow, and #7 to be the musical note.
  lcd.loadCustomCharacter(back_arrow, 6);
  lcd.loadCustomCharacter(note, 7);
}

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

  buzzer.playFromProgramSpace(beepWelcome);

  lcd.clear();
  lcd.print(F(" A-Star"));
  lcd.gotoLine(1);
  lcd.print(F(" Prime"));
  delay(1000);

  lcd.clear();
  lcd.print(F("Demo"));
  lcd.gotoLine(1);
  lcd.print(F("Program"));
  delay(1000);

  lcd.clear();
  lcd.print(F("Use B to"));
  lcd.gotoLine(1);
  lcd.print(F("select."));
  delay(1000);

  lcd.clear();
  lcd.print(F("Press B"));
  lcd.gotoLine(1);
  lcd.print(F("-try it!"));

  while(buttonMonitor() != 'B'){}

  buzzer.playFromProgramSpace(beepThankYou);
  lcd.clear();
  lcd.print(F(" Thank"));
  lcd.gotoLine(1);
  lcd.print(F("  you!"));
  delay(1000);
}

// This function prompts the user to choose something from the
// main menu, runs their selection, and then returns.
void mainMenuSelect()
{
  lcd.clear();
  lcd.print(F("  Main"));
  lcd.gotoLine(1);
  lcd.print(F("  Menu"));
  delay(1000);
  mainMenu.select();
}

void loop()
{
  mainMenuSelect();
}
