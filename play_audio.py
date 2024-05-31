import serial
from playsound import playsound
import os
import time

ARDUINO_COM = '/dev/cu.usbmodem1301'
ARDUINO_PORT = 115200
SOUND_DIR = "./chord_recordings/"

arduino = serial.Serial(ARDUINO_COM, ARDUINO_PORT)

while True:
    if arduino.in_waiting > 0:
        data = arduino.readline(arduino.in_waiting) 
        print(data.decode('utf-8'))
        # the last bit gets rid of the new-line chars
        # print(arduino.readline().decode('utf-8'))
        chord = data.decode('utf-8')[2:-1]

        if chord != ("relax"):
            print("Now playing chord: ", chord)
            playsound(SOUND_DIR + chord + ".wav")
            print("end playing")
    time.sleep(0.1)