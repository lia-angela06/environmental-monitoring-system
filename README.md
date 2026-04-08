# ESP32 Environmental Monitor

A real-time sensor display system built with an ESP32, reading ambient light (LDR), 
temperature, and humidity (DHT11) and outputting live data to a 128x64 OLED screen.

## Hardware
- ESP32 Dev Board
- LDR (photoresistor) on GPIO 2
- DHT11 Temperature & Humidity Sensor on GPIO 18
- SSD1306 128x64 OLED Display (I2C, address 0x3C)

## Features
- Non-blocking sensor polling using `millis()` timers
- Live OLED display updates for all three readings
- Serial monitor output for debugging

## Libraries Used
- `DHT11`
- `Adafruit GFX`
- `Adafruit SSD1306`
- `Wire` (I2C)

## How to Run
1. Wire up components per the pin definitions in the source file
2. Install required libraries via Arduino Library Manager
3. Upload to ESP32 using Arduino IDE
4. Open Serial Monitor at 115200 baud to view raw readings
