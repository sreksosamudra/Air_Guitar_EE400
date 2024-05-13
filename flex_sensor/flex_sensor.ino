/******************************************************************************
Flex_Sensor_Example.ino
Example sketch for SparkFun's flex sensors
  (https://www.sparkfun.com/products/10264)
Jim Lindblom @ SparkFun Electronics
April 28, 2016

Create a voltage divider circuit combining a flex sensor with a 47k resistor.
- The resistor should connect from A0 to GND.
- The flex sensor should connect from A0 to 3.3V
As the resistance of the flex sensor increases (meaning it's being bent), the
voltage at A0 should decrease.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int FLEX_PIN = A0; // Pin connected to voltage divider output
const float VCC = 4.98; // Measured voltage of Ardunio 5V line

//1st flex sensor (00723)

const float R_DIV = 9860.0; // Measured resistance of 10k resistor
const float STRAIGHT_RESISTANCE = 25000.0; // resistance when straight
const float BEND_RESISTANCE = 60000.0; // resistance at 90 deg
const float MAX_BEND_RESISTANCE = 125000.0; // max resistance

//2nd flex sensor (00523 5)
const float R_DIV_2 = 9860.0; // Measured resistance of 10k resistor
const float STRAIGHT_RESISTANCE_2 = 31000.0; // resistance when straight
const float BEND_RESISTANCE_2 = 66000.0; // resistance at 90 deg
const float MAX_BEND_RESISTANCE_2 = 125000.0; // max resistance

//3rd flex sensor (00523 25)
const float R_DIV_3 = 9860.0; // Measured resistance of 10k resistor
const float STRAIGHT_RESISTANCE_3 = 26500.0; // resistance when straight
const float BEND_RESISTANCE_3 = 61000.0; // resistance at 90 deg
const float MAX_BEND_RESISTANCE_3 = 125000.0; // max resistance

void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();

  delay(500);
}
