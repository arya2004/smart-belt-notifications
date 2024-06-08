# Setup Guide

## Hardware Setup

1. Connect the ultrasonic sensor to the ESP32:
   - Trig Pin -> GPIO 5
   - Echo Pin -> GPIO 18
   - VCC -> 5V
   - GND -> GND

## Software Setup

1. Download and install the [Arduino IDE](https://www.arduino.cc/en/Main/Software).

2. Install necessary libraries:
   - WiFi.h
   - Blynk library

3. Configure WiFi and Blynk settings in `config/wifi_config.h`.

4. Open `src/DistanceAlert.ino` in the Arduino IDE and upload it to the ESP32.

## Running the Project

1. Open the Serial Monitor to view the distance measurements.
2. If the distance is less than the threshold (50 cm), an alert will be sent to the Blynk server.
