#include <guitar_volt_inferencing.h>


/* Includes ---------------------------------------------------------------- */
#include <guitar_volt_inferencing.h>
#include <Arduino_LSM9DS1.h> //Click here to get the library: https://www.arduino.cc/reference/en/libraries/arduino_lsm9ds1/

/* Constant defines -------------------------------------------------------- */
#define NUM_ANALOG_INPUTS 4


/* Private variables ------------------------------------------------------- */
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal

/**
* @brief      Arduino setup function
*/
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
    while (!Serial);
    Serial.println("Edge Impulse Inferencing Demo using Analog Inputs");

    // Initialize analog inputs
    for (int i = 0; i < NUM_ANALOG_INPUTS; i++) {
        pinMode(A1 + i, INPUT);
    }

    Serial1.begin(9600);
}


/**
* @brief      Get data and run inferencing
*
* @param[in]  debug  Get debug info if true
*/
void loop()
{
    // ei_printf("\nStarting inferencing in 0.5 seconds\n");

    delay(100);

    // ei_printf("Sampling... ");

    // Allocate a buffer here for the values we'll read from the analog inputs
    float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };

    for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += NUM_ANALOG_INPUTS) {
        // Determine the next tick (and then sleep later)
        uint64_t next_tick = micros() + (EI_CLASSIFIER_INTERVAL_MS * 1000);

        for (int i = 0; i < NUM_ANALOG_INPUTS; i++) {
            buffer[ix + i] = analogRead(A1 + i) * (3.3f / 1023.0f); // Assuming a reference voltage of 3.3V
        }

        delayMicroseconds(next_tick - micros());
    }

    // Turn the raw buffer into a signal which we can then classify
    signal_t signal;
    int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
    if (err != 0) {
        ei_printf("Failed to create signal from buffer (%d)\n", err);
        return;
    }

    // Run the classifier
    ei_impulse_result_t result = { 0 };

    err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run classifier (%d)\n", err);
        return;
    }

    // Print the predictions
// ei_printf("Predictions ");
// ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)", result.timing.dsp, result.timing.classification, result.timing.anomaly);
// ei_printf(": \n");

float max_value = 0.0;
const char* max_label = "";

for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    // ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    
    // Check if current value is greater than the max_value found so far
    if (result.classification[ix].value > max_value) {
        max_value = result.classification[ix].value;
        max_label = result.classification[ix].label;
    }
}

// Print the label with the highest probability
// ei_printf("\nHighest probability: %s: %.5f\n", max_label, max_value);

while (Serial1.available() >= 0) {
  char receivedData = Serial1.read();
  if (receivedData == '0') {
      ei_printf("Detected: %s but not played.\n", max_label);
    }
  else if (receivedData == '1') {
      ei_printf("Playing: %s. \n", max_label);
  }
  break;
}

#if EI_CLASSIFIER_HAS_ANOMALY == 1
    // ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif
}
