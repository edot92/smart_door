#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            2         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
//#define DHTTYPE           DHT11     // DHT 11 
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  delay(1000);
  Serial.begin(9600); 

  ina219.begin();

  // Initialize device.
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}
 StaticJsonBuffer<200> jsonBuffer;
   JsonObject& root =jsonBuffer.createObject();

void loop() {

  // Delay between measurements.
  delay(delayMS);
bacaDHT();
bacaSensorINA();

  root.printTo(Serial);
  Serial.print("#");
}

void bacaDHT(){

 
    sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
  root["Temperature"] = 0;
  }
  else {
  root["Temperature"] = event.temperature;
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
 root["Humidity"] = 0;
  }
  else {
 root["Humidity"] = event.relative_humidity;
  }
  }
void bacaSensorINA(){
  
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
   root["Busvoltage"] = busvoltage;
root["Shuntvoltage"] = shuntvoltage;
root["Loadvoltage"] = loadvoltage;
root["Current"] = current_mA;
}

