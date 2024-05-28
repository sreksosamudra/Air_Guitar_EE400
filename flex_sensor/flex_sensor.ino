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
const float VCC = 4.98; // Measured voltage of Ardunio 5V line

//1st flex sensor (00723)
const int FLEX_PIN_1 = A0; // Pin connected to voltage divider output

const float R_DIV_1 = 9860.0; // Measured resistance of 10k resistor
const float STRAIGHT_RESISTANCE_1 = 14100.0; // resistance when straight
const float BEND_RESISTANCE_1 = 60000.0; // resistance at 90 deg
const float MAX_BEND_RESISTANCE_1 = 125000.0; // max resistance

//2nd flex sensor (00523 5)
const int FLEX_PIN_2 = A1; // Pin connected to voltage divider output

const float R_DIV_2 = 9880.0; // Measured resistance of 10k resistor
const float STRAIGHT_RESISTANCE_2 = 31000.0; // resistance when straight
const float BEND_RESISTANCE_2 = 66000.0; // resistance at 90 deg
const float MAX_BEND_RESISTANCE_2 = 125000.0; // max resistance

//3rd flex sensor (00523 25)
const int FLEX_PIN_3 = A2; // Pin connected to voltage divider output

const float R_DIV_3 = 9840.0; // Measured resistance of 10k resistor
const float STRAIGHT_RESISTANCE_3 = 30000.0; // resistance when straight
const float BEND_RESISTANCE_3 = 68000.0; // resistance at 90 deg
const float MAX_BEND_RESISTANCE_3 = 125000.0; // max resistance

void setup() 
{
  Serial.begin(9600);
  pinMode(FLEX_PIN_1, INPUT);
  pinMode(FLEX_PIN_2, INPUT);
  pinMode(FLEX_PIN_3, INPUT);
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC_1 = analogRead(FLEX_PIN_1);
  int flexADC_2 = analogRead(FLEX_PIN_2);
  int flexADC_3 = analogRead(FLEX_PIN_3);


  float flexV_1 = flexADC_1 * VCC / 1023.0;
  float flexR_1 = R_DIV_1 * (VCC / flexV_1 - 1.0);

  float flexV_2 = flexADC_2 * VCC / 1023.0;
  float flexR_2 = R_DIV_2 * (VCC / flexV_2 - 1.0);

  float flexV_3 = flexADC_3 * VCC / 1023.0;
  float flexR_3 = R_DIV_3 * (VCC / flexV_3 - 1.0);

  Serial.println("Resistance flex1: " + String(flexR_1) + " ohms");

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle_1 = map(flexR_1, STRAIGHT_RESISTANCE_1, BEND_RESISTANCE_2,
                   0, 90.0);
  Serial.println("Bend1: " + String(angle_1) + " degrees");
  Serial.println();


  Serial.println("Resistance flex2: " + String(flexR_2) + " ohms");

  float angle_2 = map(flexR_2, STRAIGHT_RESISTANCE_1, BEND_RESISTANCE_2,
                   0, 90.0);
  Serial.println("Bend2: " + String(angle_2) + " degrees");
  Serial.println();


  Serial.println("Resistance flex3: " + String(flexR_3) + " ohms");

  float angle_3 = map(flexR_3, STRAIGHT_RESISTANCE_1, BEND_RESISTANCE_2,
                   0, 90.0);
  Serial.println("Bend3: " + String(angle_3) + " degrees");
  Serial.println();

  delay(2000);
}
