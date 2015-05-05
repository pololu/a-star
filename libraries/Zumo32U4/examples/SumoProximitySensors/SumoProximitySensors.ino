/* This example shows how you might use the Zumo 32U4 in a robot
sumo competition.

It uses the line sensors to detect the white border of the sumo
ring so it can avoid driving out of the ring (similar to the
BorderDetect example).  It also uses the Zumo 32U4's proximity
sensors to scan for nearby opponents and drive towards them.

For this code to work, jumpers on the front sensor array
must be installed in order to connect pin 4 to RGT and connect
pin 20 to LFT.

This code was tested on a Zumo 32U4 with 75:1 HP micro metal
gearmotors. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4ButtonA buttonA;
Zumo32U4Buzzer buzzer;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;

unsigned int lineSensorValues[3];

// When the reading on a line sensor goes below this value, we
// consider that line sensor to have detected the white border at
// the edge of the ring.  This value might need to be tuned for
// different lighting conditions, surfaces, etc.
const uint16_t lineSensorThreshold = 1000;

// The speed that the robot uses when backing up.
const uint16_t reverseSpeed = 200;

// The speed that the robot uses when turning.
const uint16_t turnSpeed = 200;

// The speed that the robot usually uses when moving forward.
// You don't want this to be too fast because then the robot
// might fail to stop when it detects the white border.
const uint16_t forwardSpeed = 200;

// These two variables specify the speeds to apply to the motors
// when veering left or veering right.  While the robot is
// driving forward, it uses its proximity sensors to scan for
// objects ahead of it and tries to veer towards them.
const uint16_t veerSpeedLow = 0;
const uint16_t veerSpeedHigh = 250;

// The speed that the robot drives when it detects an opponent in
// front of it, either with the proximity sensors or by noticing
// that it is caught in a stalemate (driving forward for several
// seconds without reaching a border).  400 is full speed.
const uint16_t rammingSpeed = 400;

// The amount of time to spend backing up after detecting a
// border, in milliseconds.
const uint16_t reverseTime = 200;

// The minimum amount of time to spend scanning for nearby
// opponents, in milliseconds.
const uint16_t scanTimeMin = 200;

// The maximum amount of time to spend scanning for nearby
// opponents, in milliseconds.
const uint16_t scanTimeMax = 2100;

// The amount of time to wait between detecting a button press
// and actually starting to move, in milliseconds.  Typical robot
// sumo rules require 5 seconds of waiting.
const uint16_t waitTime = 5000;

// If the robot has been driving forward for this amount of time,
// in milliseconds, without reaching a border, the robot decides
// that it must be pushing on another robot and this is a
// stalemate, so it increases its motor speed.
const uint16_t stalemateTime = 4000;

// This enum lists the top-level states that the robot can be in.
enum State
{
  StatePausing,
  StateWaiting,
  StateScanning,
  StateDriving,
  StateBacking,
};

State state = StatePausing;

enum Direction
{
  DirectionLeft,
  DirectionRight,
};

// scanDir is the direction the robot should turn the next time
// it scans for an opponent.
Direction scanDir = DirectionLeft;

// The time, in milliseconds, that we entered the current top-level state.
uint16_t stateStartTime;

// The time, in milliseconds, that the LCD was last updated.
uint16_t displayTime;

// This gets set to true whenever we change to a new state.
// A state can read and write this variable this in order to
// perform actions just once at the beginning of the state.
bool justChangedState;

// This gets set whenever we clear the display.
bool displayCleared;

void setup()
{
  // Uncomment if necessary to correct motor directions:
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);

  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();

  changeState(StatePausing);
}

void loop()
{
  bool buttonPress = buttonA.getSingleDebouncedPress();

  if (state == StatePausing)
  {
    // We are in the pausing state, so just wait for the user to
    // press button A, while displaying the batter voltage every
    // 100 ms.

    if (justChangedState)
    {
      justChangedState = false;
      lcd.print(F("Press A"));
    }

    motors.setSpeeds(0, 0);

    if (displayIsStale(100))
    {
      displayUpdated();
      lcd.gotoXY(0, 1);
      lcd.print(readBatteryMillivolts());
    }

    if (buttonPress)
    {
      changeState(StateWaiting);
    }
  }
  else if (buttonPress)
  {
    // The user pressed button A while the robot was running, so pause.
    changeState(StatePausing);
  }
  else if (state == StateWaiting)
  {
    uint16_t time = timeInThisState();
    uint16_t timeLeft = waitTime - time;

    lcd.gotoXY(0, 0);
    lcd.print(timeLeft / 1000 % 10);
    lcd.print('.');
    lcd.print(timeLeft / 100 % 10);

    // TODO: beep every second

    if (time >= waitTime)
    {
      changeState(StateScanning);
    }
  }
  else if (state == StateBacking)
  {
    if (justChangedState)
    {
      justChangedState = false;
      lcd.print(F("back"));
    }

    motors.setSpeeds(-reverseSpeed, -reverseSpeed);

    if (timeInThisState() >= reverseTime)
    {
      changeState(StateScanning);
    }
  }
  else if (state == StateScanning)
  {
    if (justChangedState)
    {
      justChangedState = false;
      lcd.print(F("scan"));
    }

    if (scanDir == DirectionRight)
    {
      motors.setSpeeds(turnSpeed, -turnSpeed);
    }
    else
    {
      motors.setSpeeds(-turnSpeed, turnSpeed);
    }

    uint16_t time = timeInThisState();

    if (time > scanTimeMin)
    {
      proxSensors.read();
      if (proxSensors.countsFrontWithLeftLeds() > 1)
      {
        changeState(StateDriving);
      }
      if (proxSensors.countsFrontWithRightLeds() > 1)
      {
        changeState(StateDriving);
      }
    }

    if (time > scanTimeMax)
    {
      changeState(StateDriving);
    }
  }
  else if (state == StateDriving)
  {
    if (justChangedState)
    {
      justChangedState = false;
      lcd.print(F("drive"));
    }

    // Check for borders.
    lineSensors.read(lineSensorValues);
    if (lineSensorValues[0] < lineSensorThreshold)
    {
      scanDir = DirectionRight;
      changeState(StateBacking);
    }
    if (lineSensorValues[2] < lineSensorThreshold)
    {
      scanDir = DirectionLeft;
      changeState(StateBacking);
    }

    // Try to drive towards the opponent.
    proxSensors.read();
    uint8_t sum = proxSensors.countsFrontWithRightLeds() + proxSensors.countsFrontWithLeftLeds();
    int8_t diff = proxSensors.countsFrontWithRightLeds() - proxSensors.countsFrontWithLeftLeds();

    // You might also consider using encoders to detect a
    // stalemate, but that might be difficult if the robot's
    // treads are slipping.
    if (sum >= 4 || timeInThisState() > stalemateTime)
    {
      motors.setSpeeds(rammingSpeed, rammingSpeed);
      ledRed(1);
    }
    else if (sum == 0)
    {
      motors.setSpeeds(forwardSpeed, forwardSpeed);
      if (proxSensors.countsLeftWithLeftLeds() >= 2)
      {
        scanDir = DirectionLeft;
        changeState(StateScanning);
      }
      if (proxSensors.countsRightWithRightLeds() >= 2)
      {
        scanDir = DirectionRight;
        changeState(StateScanning);
      }
    }
    else
    {
      if (diff >= 1)
      {
        // Veer to the right.
        motors.setSpeeds(veerSpeedHigh, veerSpeedLow);
      }
      else if (diff <= -1)
      {
        // Veer to the left.
        motors.setSpeeds(veerSpeedLow, veerSpeedHigh);
      }
      else
      {
        motors.setSpeeds(forwardSpeed, forwardSpeed);
      }
      ledRed(0);
    }
  }
}

// Gets the amount of time we have been in this state, in
// milliseconds.  After 65535 milliseconds (65 seconds), this
// overflows to 0.
uint16_t timeInThisState()
{
  return (uint16_t)(millis() - stateStartTime);
}

// Changes to a new state.  It also clears the LCD and turns off
// the LEDs so that the things the previous state were doing do
// not affect the feedback the user sees in the new state.
void changeState(uint8_t newState)
{
  state = (State)newState;
  justChangedState = true;
  stateStartTime = millis();
  ledRed(0);
  ledYellow(0);
  ledGreen(0);
  lcd.clear();
  displayCleared = true;
}

// Returns true if the display has been cleared or the contents
// on it have not been updated in a while.  The time limit used
// to decide if the contents are staled is specified in
// milliseconds by the staleTime parameter.
bool displayIsStale(uint16_t staleTime)
{
  return displayCleared || (millis() - displayTime) > staleTime;
}

// Any part of the code that uses displayIsStale to decide when
// to update the LCD should call this function after updating the
// LCD.
void displayUpdated()
{
  displayTime = millis();
  displayCleared = false;
}
