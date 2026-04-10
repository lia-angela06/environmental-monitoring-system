#include <DHT11.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LDR 2
#define dht_pin 18
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDRESS 0x3C
#define OLED_RESET -1

DHT11 dht(dht_pin);
Adafruit_SSD1306 screen(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

int16_t dt = 1000;
int16_t lastLDR = 0;
int16_t lastHumidity = 0;
int16_t lastTemp = 0;

//LDR
unsigned long timeNow;
unsigned long pastTime;
unsigned long threshold = 500;

//DHT
unsigned long dht_timeNow;
unsigned long dht_pastTime;
unsigned long dht_threshold = 500;

void setup() {
  Serial.begin(115200);
  pinMode(LDR, INPUT);
  
  pastTime = millis();
  dht_pastTime = millis();

  screen.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

  screen.clearDisplay();
  screen.setCursor(0,0);
  screen.setTextSize(1);
  screen.setTextColor(SSD1306_WHITE);

  screen.display();

}

void oledScreen(int16_t LDR_reading, int16_t reading, int16_t tepReading);

void loop() {
  

  timeNow = millis();
  if(timeNow - pastTime >= threshold){
    pastTime = timeNow;
    LDR_data();
  }

  dht_timeNow = millis();
  if(dht_timeNow - dht_pastTime >= dht_threshold){
    dht_pastTime = dht_timeNow;
    DHT_data();
  }


}

void oledScreen(int16_t LDR_reading, int16_t reading, int16_t tepReading){
  screen.clearDisplay();
  screen.setTextSize(1);
  screen.setTextColor(SSD1306_WHITE);

  screen.setCursor(0,0);
  screen.print("Light: ");
  screen.print(LDR_reading);

  screen.setCursor(0, 20);
  screen.print("Humidity: ");
  screen.print(reading);
  screen.println("%");

  screen.setCursor(0, 40);
  screen.print("Temp: ");
  screen.print(tepReading);
  screen.println(" C");

  screen.display();
}

void LDR_data(){
  lastLDR = analogRead(LDR);
  Serial.print("LDR reading: ");
  Serial.println(lastLDR);
  oledScreen(lastLDR, lastHumidity, lastTemp);
}

void DHT_data(){
  lastHumidity = dht.readHumidity();
  lastTemp = dht.readTemperature();
  
  Serial.print("Humidity: ");
  Serial.println(lastHumidity);
  Serial.print("Temp: ");
  Serial.println(lastTemp);
  oledScreen(lastLDR, lastHumidity, lastTemp);
}
