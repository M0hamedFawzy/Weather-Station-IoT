# ESP32 Weather Station with DHT11 and BMP180 Sensors

This project is an ESP32-based weather station that collects temperature and humidity data from a DHT11 sensor and temperature, pressure, and altitude data from a BMP180 sensor. The data is displayed on a web interface served by the ESP32.

## Components Used
- ESP32
- DHT11 Sensor
- BMP180 Sensor
- Breadboard and Jumper Wires
- LCD 16x2
  

## Setup and Usage

1. **Hardware Connections:**
   - Connect the DHT11 sensor to GPIO4 of the ESP32.
   - Connect the BMP180 sensor to the I2C pins (SDA and SCL) of the ESP32.
   - Power both sensors with 3.3V from the ESP32.

2. **Software:**
   - Install the required libraries in your Arduino IDE:
     - `Adafruit_Sensor`
     - `DHT`
     - `Adafruit_BMP085`
     - `ESPAsyncWebServer`
     - `AsyncTCP`

3. **Code:**
   - Upload the provided C code to your ESP32.

4. **Accessing the Web Interface:**
   - Connect to the same Wi-Fi network as your ESP32.
   - Find the IP address of your ESP32 in the Serial Monitor.
   - Open a web browser and go to `http://<ESP32_IP_ADDRESS>` to access the weather station web interface.

## Features

- Real-time temperature and humidity readings from the DHT11 sensor.
- Real-time temperature, pressure, and altitude readings from the BMP180 sensor.
- A user-friendly web interface to display the sensor data.
- Periodic updates of the sensor data every 5 seconds.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

 
