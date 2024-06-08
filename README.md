# Air Musician EE400
Explore the repository for the EE400 (TinyML) final project—an innovative air guitar system. This project harnesses gesture motion detected by flex sensors and accelerometers, enabling users to experience the magic of playing an air guitar like never before.

## How to Use
The repository contains the codes required from data collection to model deployment. However, the model training part is done through [Edge Impulse](https://www.edgeimpulse.com/), a platform that simplifies the process of developing machine learning models for edge devices. Following the steps below will guide you through the process of data collection, model training, and deployment.

## Repository Structure
The repository is structured as follows:
```
.
├── chord_recordings
│   ├── A, C, C7, D, E, Em, G chord recordings in .wav
├── data_collect
│   ├── hold30-p
│   │   └── A, C, C7, D, E, Em, G flex data in .csv
│   ├── relax
│   │   └── relax flex data in .csv
│   ├── data_collect.ino
│   ├── sensor_data.csv
│   ├── serial_to_csv.py
├── glv-trans
│   ├── acc_uart
│   │   ├── acc_uart.ino
│   ├── glv_uart
│   │   ├── glv_uart.ino
├── play_audio.py
├── README.md
├── trim.py
```
### Data Collection
As a highly customizable project to ensure the best user experience, the data collection process is divided into two parts: data collection and data preprocessing. The data collection part is done using the Arduino IDE, while the data preprocessing part is done using Python. The data collection part is further divided into two categories: `hold30-p` and `relax`. The `hold30-p` category is used to collect data for the chord positions with holding them for 30s, while the `relax` category is used to collect data for the relaxed position. The data collected is stored in the `sensor_data.csv` file. The `serial_to_csv.py` script is used to monitor the serial port and save the data to the `sensor_data.csv` file. The sample rate, resistor connected, and baud rate can be adjusted in the `data_collect.ino` file.

### Model Training
The model training part is done using Edge Impulse. The `chord_recordings` folder contains the .wav files for the chords A, C, C7, D, E, Em, and G. These files are used to train the model. Edge Impulse can help export the trained model to the Arduino IDE to be properly included in the Arduino code. In our setup, we used raw data from the flex sensors and accelerometer to train the model. Classification was done to classify the chords and the relaxed position. The output of the flex model should be the number of classes + 1 (relaxed position) depending on the number of chords you want to classify. The output of the accelerometer model should be either strum or idle.

With proper training and data collection, the model should have a high accuracy. For reference, our model for the flex sensors consists of 4 feature inputs, 1 dense layer with 20 neurons, 1 dense layer with 10, 1 dropout layer with rate 0.5, and the output layer with 8 classes. The model for the accelerometer consists of 39 feature inputs, 1 dense layer with 20 neurons, 1 dense layer with 10 neurons, and the output layer with 2 classes.