// import to read local files
// export the 4 channel flex sensor data to a csv file as resistance values
const float VCC = 3.3; // Measured voltage of Ardunio 3.3V line
const float STRAIGHT_RESISTANCE_1 = 28000.0; // resistance when straight for 1
const float STRAIGHT_RESISTANCE_2 = 33500.0; // resistance when straight for 2
const float STRAIGHT_RESISTANCE_3 = 26000.0; // resistance when straight for 3
const float STRAIGHT_RESISTANCE_4 = 28000.0; // resistance when straight for 4

const float MAX_BEND_RESISTANCE_1 = 60000.0; // max resistance for 1
const float MAX_BEND_RESISTANCE_2 = 60000.0; // max resistance for 2
const float MAX_BEND_RESISTANCE_3 = 60000.0; // max resistance for 3
const float MAX_BEND_RESISTANCE_4 = 60000.0; // max resistance for 4

const int FLEX_PIN_1 = A1; // 007 23 1
const int FLEX_PIN_2 = A2; // 007 23 20
const int FLEX_PIN_3 = A3; // 005 23 25
const int FLEX_PIN_4 = A4; // 005 23 5

const int R_DIV = 10000.0; // Measured resistance of 47k resistor
// const int R_DIV = 5.3;
void setup() {
	// pins for the 4 flex sensors
	pinMode(FLEX_PIN_1, INPUT); // for finger 1 (index)
	pinMode(FLEX_PIN_2, INPUT); // for finger 2 (middle)
	pinMode(FLEX_PIN_3, INPUT); // for finger 3 (ring)
	pinMode(FLEX_PIN_4, INPUT); // for finger 4 (pinky)

	// start serial communication
	Serial.begin(115200);

	// add a delay to let the serial monitor start
	delay(2000);

	// print the header of the csv file
	Serial.println("index,middle,ring,pinky");
}


void readFlexSensors() {
	// read the resistance values of the 4 flex sensors as ADC values
	int flex1 = analogRead(FLEX_PIN_1);
	int flex2 = analogRead(FLEX_PIN_2);
	int flex3 = analogRead(FLEX_PIN_3);
	int flex4 = analogRead(FLEX_PIN_4);

	// voltage values
	float flexV1 = flex1 * VCC / 1023.0;
	float flexV2 = flex2 * VCC / 1023.0;
	float flexV3 = flex3 * VCC / 1023.0;
	float flexV4 = flex4 * VCC / 1023.0;

	// // resistance values
	// float flexR1 = R_DIV * (VCC / flexV1 - 1.0);
	// float flexR2 = R_DIV * (VCC / flexV2 - 1.0);
	// float flexR3 = R_DIV * (VCC / flexV3 - 1.0);
	// float flexR4 = R_DIV * (VCC / flexV4 - 1.0);

	// // angle
	// float angle1 = map(flexR1, STRAIGHT_RESISTANCE_1, MAX_BEND_RESISTANCE_1, 0, 90.0);
	// float angle2 = map(flexR2, STRAIGHT_RESISTANCE_2, MAX_BEND_RESISTANCE_2, 0, 90.0);
	// float angle3 = map(flexR3, STRAIGHT_RESISTANCE_3, MAX_BEND_RESISTANCE_3, 0, 90.0);
	// float angle4 = map(flexR4, STRAIGHT_RESISTANCE_4, MAX_BEND_RESISTANCE_4, 0, 90.0);

	// just print the resistance values in 4 columns, writing the file will be done with python
	Serial.print(flexV1);
	Serial.print(",");
	Serial.print(flexV2);
	Serial.print(",");
	Serial.print(flexV3);
	Serial.print(",");
	Serial.println(flexV4);
}

void loop() {
  // put your main code here, to run repeatedly:
  readFlexSensors();
  delay(100); // 1 sample every 100 ms = 10 samples per second = 600 samples per minute
//   delay(50); // 1 sample every 50 ms = 20 samples per second = 1200 samples per minute
}
