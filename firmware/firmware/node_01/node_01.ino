#include "DHT.h"

// Pin Definitions
#define DHTPIN 23        // DHT22 connected to GPIO 23
#define DHTTYPE DHT22    // DHT 22 (AM2302)
#define MQ135PIN 34      // MQ-135 connected to GPIO 34 (Analog)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start Serial Communication with Mac
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("=================================");
  Serial.println(" ESP32 Sensor Node Test Starting ");
  Serial.println("=================================");

  // Initialize DHT22 Sensor
  dht.begin();
  pinMode(MQ135PIN, INPUT);
}

void loop() {
  // Read Temperature and Humidity from DHT22
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  // Read Raw Analog Value from MQ-135 (0 - 4095)
  int mqRaw = analogRead(MQ135PIN);
  float voltage = (mqRaw / 4095.0) * 3.3; // Convert to voltage level

  // Check if DHT22 read failed
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println("⚠️ Warning: Failed to read from DHT22 sensor! Check wiring.");
  } else {
    Serial.print("🌡️ Temp: ");
    Serial.print(tempF);
    Serial.print(" °F | 💧 Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // Display Air Quality Readings
  Serial.print("🌬️ Air Quality Raw ADC: ");
  Serial.print(mqRaw);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");
  
  Serial.println("---------------------------------");

  // Wait 2 seconds before next reading
  delay(2000);
}

