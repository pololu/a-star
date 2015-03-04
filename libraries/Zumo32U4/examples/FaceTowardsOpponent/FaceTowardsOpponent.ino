/** This example uses the front proximity sensor on the Zumo 32U4
Front Sensor Array to locate an opponent robot or any other
reflective object.  Using the motors to turn, it scans its
surroundings.  If it senses an object, it turns on its yellow
LED and attempts to face towards that object. */

#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4LCD lcd;
Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;

#define LEFT 0
#define RIGHT 1

const uint8_t sensorThreshold = 1;
const uint16_t turnSpeedMax = 400; // was 300
const uint16_t turnSpeedMin = 100;
const uint16_t deceleration = 10;
const uint16_t acceleration = 10;

bool senseDir = RIGHT;
bool turningLeft = false;
bool turningRight = false;
uint16_t lastTimeObjectSeen = 0;
uint16_t turnSpeed = turnSpeedMax;

uint8_t cyclesSinceLastReversal = 255;
uint8_t shortReversalCount = 0;

void setup()
{
  proxSensors.initFrontSensor();

  // Wait for the user to press A before driving the motors.
  lcd.clear();
  lcd.print(F("Press A"));
  buttonA.waitForButton();
  lcd.clear();
}

void turnRight()
{
  motors.setSpeeds(turnSpeed, -turnSpeed);
  turningLeft = false;
  turningRight = true;
}

void turnLeft()
{
  motors.setSpeeds(-turnSpeed, turnSpeed);
  turningLeft = true;
  turningRight = false;
}

void stop()
{
  motors.setSpeeds(0, 0);
  turningLeft = false;
  turningRight = false;
}

void loop()
{
  proxSensors.read();
  uint8_t leftValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightValue = proxSensors.countsFrontWithRightLeds();

  bool objectSeen = leftValue >= sensorThreshold || rightValue >= sensorThreshold;

  if (objectSeen)
  {
    turnSpeed -= deceleration;
  }
  else
  {
    turnSpeed += acceleration;
  }
  turnSpeed = constrain(turnSpeed, turnSpeedMin, turnSpeedMax);

  if (objectSeen)
  {
    // Object seen.
    ledYellow(1);

    lastTimeObjectSeen = millis();

    bool lastTurnRight = turnRight;

    if (leftValue < rightValue)
    {
      turnRight();
      senseDir = RIGHT;
    }
    else if (leftValue > rightValue)
    {
      turnLeft();
      senseDir = LEFT;
    }
    else
    {
      stop();
    }
  }
  else
  {
    // No object seen, so just keep turning.
    ledYellow(0);

    if (senseDir == RIGHT)
    {
      turnRight();
    }
    else
    {
      turnLeft();
    }
  }

  lcd.gotoXY(0, 0);
  lcd.print(leftValue);
  lcd.print(' ');
  lcd.print(rightValue);
  lcd.gotoXY(0, 1);
  lcd.print(turningRight ? 'R' : (turningLeft ? 'L' : ' '));
  lcd.print(' ');
  lcd.print(turnSpeed);
  lcd.print(' ');
  lcd.print(' ');
}
