/** This file provides functions for moving on a line grid.  It
uses the line sensors to follow lines and detect intersections,
and it uses the L3GD20H gyro to help perform turns.

This code was designed with maze-solving in mind, but it can be
used in other applications as long as there are black lines on a
white surface, and the lines are not too close together, and the
lines intersect at right angles. */

#include "GridMovement.h"

uint16_t lineSensorValues[numSensors];

int16_t gyroOffset;
uint16_t gyroLastUpdate = 0;
uint32_t gyroAngle = 0;

// Sets up special characters in the LCD so that we can display
// bar graphs.
static void loadCustomCharacters()
{
  static const char levels[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63
  };
  lcd.loadCustomCharacter(levels + 0, 0);  // 1 bar
  lcd.loadCustomCharacter(levels + 1, 1);  // 2 bars
  lcd.loadCustomCharacter(levels + 2, 2);  // 3 bars
  lcd.loadCustomCharacter(levels + 3, 3);  // 4 bars
  lcd.loadCustomCharacter(levels + 4, 4);  // 5 bars
  lcd.loadCustomCharacter(levels + 5, 5);  // 6 bars
  lcd.loadCustomCharacter(levels + 6, 6);  // 7 bars
}

void printBar(uint8_t height)
{
  if (height > 8) { height = 8; }
  const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, 255};
  lcd.print(barChars[height]);
}

// Reset the gyro angle to zero and prepare to keep track of it.
void gyroAngleReset()
{
  gyroLastUpdate = micros();
  gyroAngle = 0;
}

// Read the gyro and update the angle.  This should be called as
// frequently as possible while using the gyro to do turns.
void gyroAngleUpdate()
{
  uint16_t m = micros();
  uint16_t dt = m - gyroLastUpdate;
  gyroLastUpdate = m;

  // (70 mdps/digit) * (1/1000 dps/mdps) * (1/1000000 s/us) * (2^29/45 unit/degree)
  // = 14680064/17578125 unit/us/digit

  gyro.read();

  gyroAngle += (int64_t)((int32_t)(gyro.g.z - gyroOffset) * dt) * 14680064 / 17578125;
}

// Calibrates the gyro.  The digital zero-rate level of the
// L3GD20H gyro can be as high as 25 degrees per second, and this
// calibration helps us correct for that.  It is important for
// the robot to be stationary during this time.
static void gyroSetup()
{
  Wire.begin();
  gyro.init();
  gyro.writeReg(L3G::CTRL_REG1, 0xFF); // 800 Hz ODR, LPF cutoff 100 Hz
  gyro.writeReg(L3G::CTRL_REG4, 0x20); // 2000 dps FS
  gyro.writeReg(L3G::CTRL_REG5, 0x00); // HPF off

  lcd.clear();
  lcd.print(F("Gyro cal"));

  // Delay to give the user time to remove their finger.
  delay(500);

  int32_t total = 0;
  for (uint16_t i = 0; i < 1024; i++)
  {
    while(!gyro.readReg(L3G::STATUS_REG & 0x08));
    gyro.read();
    total += gyro.g.z;
  }
  gyroOffset = total / 1024;

  // Display the angle (in degrees) until the user presses A.
  lcd.clear();
  gyroAngleReset();
  while (!buttonA.getSingleDebouncedRelease())
  {
    gyroAngleUpdate();
    lcd.gotoXY(0, 0);
    lcd.print(((gyroAngle >> 16) * 360) >> 16);
    lcd.print(F("   "));
  }
}

// Takes calibrated readings of the lines sensors and stores them
// in lineSensorValues.  Also returns an estimation of the line
// position.
uint16_t readSensors()
{
  return lineSensors.readLine(lineSensorValues);
}

// Returns true if the sensor is seeing a line.
// Make sure to call readSensrs() before calling this.
bool aboveLine(uint8_t sensorIndex)
{
  return lineSensorValues[sensorIndex] > sensorThreshold;
}

// Returns true if the sensor is seeing a lot of darkness.
// Make sure to call readSensrs() before calling this.
bool aboveLineDark(uint8_t sensorIndex)
{
  return lineSensorValues[sensorIndex] > sensorThresholdDark;
}

// Checks to see if we are over a dark spot, like the ones used
// to mark the end of a maze.  If all the middle sensors are over
// dark black, that means we have found the spot.
// Make sure to call readSensrs() before calling this.
bool aboveDarkSpot()
{
  return aboveLineDark(1) && aboveLineDark(2) && aboveLineDark(3);
}

// Calibrates the line sensors by turning left and right, then
// displays a bar graph of calibrated sensor readings on the LCD.
// Returns after the user presses A.
static void lineSensorSetup()
{
  lcd.clear();
  lcd.print(F("Line cal"));

  // Delay so the robot does not move while the user is still
  // touching the button.
  delay(1000);

  // We use the gyro to turn so that we don't turn more than
  // necessary, and so that if there are issues with the gyro
  // then you will know before actually starting the robot.

  gyroAngleReset();

  // Turn to the left 90 degrees.
  motors.setSpeeds(-calibrationSpeed, calibrationSpeed);
  while((int32_t)gyroAngle < gyroAngle45 * 2)
  {
    lineSensors.calibrate();
    gyroAngleUpdate();
  }

  // Turn to the right 90 degrees.
  motors.setSpeeds(calibrationSpeed, -calibrationSpeed);
  while((int32_t)gyroAngle > -gyroAngle45 * 2)
  {
    lineSensors.calibrate();
    gyroAngleUpdate();
  }

  // Turn back to center using the gyro.
  motors.setSpeeds(-calibrationSpeed, calibrationSpeed);
  while((int32_t)gyroAngle < 0)
  {
    lineSensors.calibrate();
    gyroAngleUpdate();
  }

  // Stop the motors.
  motors.setSpeeds(0, 0);

  // Show the line sensor readings on the LCD until button A is
  // pressed.
  lcd.clear();
  while(!buttonA.getSingleDebouncedPress())
  {
    readSensors();

    lcd.gotoXY(0, 0);
    for (uint8_t i = 0; i < numSensors; i++)
    {
      uint8_t barHeight = map(lineSensorValues[i], 0, 1000, 0, 8);
      printBar(barHeight);
    }
  }

  lcd.clear();
}

// Turns according to the parameter dir, which should be 'L'
// (left), 'R' (right), 'S' (straight), or 'B' (back).  We turn
// most of the way using the gyro, and then use one of the line
// sensors to finish the turn.  We use the inner line sensor that
// is closer to the target line in order to reduce overshoot.
void turn(char dir)
{
  if (dir == 'S')
  {
    // Don't do anything!
    return;
  }

  gyroAngleReset();

  uint8_t sensorIndex;

  switch(dir)
  {
  case 'B':
    // Turn left 125 degrees using the gyro.
    motors.setSpeeds(-turnSpeed, turnSpeed);
    while((int32_t)gyroAngle < gyroAngle45 * 3)
    {
      gyroAngleUpdate();
    }
    sensorIndex = 1;
    break;

  case 'L':
    // Turn left 45 degrees using the gyro.
    motors.setSpeeds(-turnSpeed, turnSpeed);
    while((int32_t)gyroAngle < gyroAngle45)
    {
      gyroAngleUpdate();
    }
    sensorIndex = 1;
    break;

  case 'R':
    // Turn right 45 degrees using the gyro.
    motors.setSpeeds(turnSpeed, -turnSpeed);
    while((int32_t)gyroAngle > -gyroAngle45)
    {
      gyroAngleUpdate();
    }
    sensorIndex = 3;
    break;

  default:
    // This should not happen.
    return;
  }

  // Turn the rest of the way using the line sensors.
  while(1)
  {
    readSensors();
    if (aboveLine(sensorIndex))
    {
      // We found the line again, so the turn is done.
      break;
    }
  }
}

// This function causes the robot to follow a line segment until
// it detects an intersection, a dead end, or a dark spot.
void followSegment()
{
  while(1)
  {
    // Get the position of the line.
    uint16_t position = readSensors();

    // Our "error" is how far we are away from the center of the
    // line, which corresponds to position 2000.
    int16_t error = (int16_t)position - 2000;

    // Compute the difference between the two motor power
    // settings, leftSpeed - rightSpeed.
    int16_t speedDifference = error / 4;

    // Get individual motor speeds.  The sign of speedDifference
    // determines if the robot turns left or right.
    int16_t leftSpeed = (int16_t)straightSpeed + speedDifference;
    int16_t rightSpeed = (int16_t)straightSpeed - speedDifference;

    // Constrain our motor speeds to be between 0 and straightSpeed.
    leftSpeed = constrain(leftSpeed, 0, (int16_t)straightSpeed);
    rightSpeed = constrain(rightSpeed, 0, (int16_t)straightSpeed);

    motors.setSpeeds(leftSpeed, rightSpeed);

    // We use the inner four sensors (1, 2, 3, and 4) for
    // determining whether there is a line straight ahead, and the
    // sensors 0 and 5 for detecting lines going to the left and
    // right.
    //
    // This code could be improved by skipping the checks below
    // if less than 200 ms has passed since the beginning of this
    // function.  Maze solvers sometimes end up in a bad position
    // after a turn, and if one of the far sensors is over the
    // line then it could cause a false intersection detection.

    if(!aboveLine(0) && !aboveLine(1) && !aboveLine(2) && !aboveLine(3) && !aboveLine(4))
    {
      // There is no line visible ahead, and we didn't see any
      // intersection.  Must be a dead end.
      break;
    }

    if(aboveLine(0) || aboveLine(4))
    {
      // Found an intersection or a dark spot.
      break;
    }
  }
}

// This should be called after followSegment to drive to the
// center of an intersection.
void driveToIntersectionCenter()
{
  // Drive to the center of the intersection.
  motors.setSpeeds(straightSpeed, straightSpeed);
  delay(intersectionDelay);
}

// This should be called after followSegment to drive to the
// center of an intersection.  It also uses the line sensors to
// detect left, straight, and right exits.
void driveToIntersectionCenter(bool * foundLeft, bool * foundStraight, bool * foundRight)
{
  *foundLeft = 0;
  *foundStraight = 0;
  *foundRight = 0;

  // Drive stright forward to get to the center of the
  // intersection, while simultaneously checking for left and
  // right exits.
  //
  // readSensors() takes approximately 2 ms to run, so we use
  // it for our loop timing.  A more robust approach would be
  // to use millis() for timing.
  motors.setSpeeds(straightSpeed, straightSpeed);
  for(uint16_t i = 0; i < intersectionDelay / 2; i++)
  {
    readSensors();
    if(aboveLine(0))
    {
      *foundLeft = 1;
    }
    if(aboveLine(4))
    {
      *foundRight = 1;
    }
  }

  readSensors();

  // Check for a straight exit.
  if(aboveLine(1) || aboveLine(2) || aboveLine(3))
  {
    *foundStraight = 1;
  }
}

void gridMovementSetup()
{
  // Configure the pins used for the line sensors.
  lineSensors.initFiveSensors();

  // Set up custom characters on the LCD so we can show a bar
  // graph of the sensor readings after calibration.
  loadCustomCharacters();

  // Calibrate the gyro and show readings from it until the user
  // presses button A.
  gyroSetup();

  // Calibrate the sensors by turning left and right, and show
  // readings from it until the user presses A again.
  lineSensorSetup();
}
