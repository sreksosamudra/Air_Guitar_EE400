import serial
import csv
import time

# Open serial port
ser = serial.Serial('/dev/cu.usbmodem1201', 115200)

# Generate a filename with a timestamp
timestamp = time.strftime("%Y%m%d-%H%M%S")
filename = f'/Users/brenda/Desktop/Working/TinyML/Air_Guitar_EE400/data_collect/sensor_data_{timestamp}.csv'

# Open or create a CSV file
with open(filename, mode='w') as file:
    writer = csv.writer(file)
    writer.writerow(['index', 'middle', 'ring', 'pinky'])  # Write the header

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()  # Read from serial and decode
            sensor_values = line.split(',')  # Split the comma-separated values
            if len(sensor_values) == 4:  # Ensure there are exactly four values
                writer.writerow(sensor_values)  # Write the sensor values directly