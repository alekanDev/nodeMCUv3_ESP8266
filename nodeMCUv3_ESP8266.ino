//PROJECT BASE TO NODEMCU V3 (ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DHT11.h>

#include "sensitiveData.h"

DHT11 dht11(5);

ESP8266WiFiMulti wifiMulti;
byte cont = 0;
byte max_intentos = 50;
const uint32_t connectTimeoutMS = 5000;

// int tempControl = 5;

int wifiConnection() {
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(SSID_company, PASS_company);
  wifiMulti.addAP(SSID_home, PASS_home);
  wifiMulti.addAP(SSID_mobile, PASS_mobile);

  while (WiFi.waitForConnectResult() != WL_CONNECTED && cont < max_intentos) {
    cont++;
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (wifiMulti.run(connectTimeoutMS) == WL_CONNECTED) {
    Serial.println("**********************************************");
    Serial.print("Conectado a la red WiFi: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
    Serial.println("**********************************************");
  } else {
    Serial.println("-------------------------------------------");
    Serial.println("Error en conexión...");
    Serial.println("-------------------------------------------");
  }
  return 1;
};

int otaMode() {
  Serial.println("\n");
  ArduinoOTA.setHostname("nodeMCUv3");  // IS THE BOARD NAME
  ArduinoOTA.setPassword("admin");      // IS SECRET PASS TO CONNECTION
  ArduinoOTA.setPort(8266);             // PORT IS NUMERIC VALUE

  ArduinoOTA.begin();
  return 1;
};

int temperatureControl() {
  // Attempt to read the temperature and humidity values from the DHT11 sensor.
  int temperature = dht11.readTemperature();

  // If using ESP32 or ESP8266 (xtensa architecture), uncomment the delay below.
  // This ensures stable readings when calling methods consecutively.
  // delay(50);

  int humidity = dht11.readHumidity();

  // Check the results of the readings.
  // If there are no errors, print the temperature and humidity values.
  // If there are errors, print the appropriate error messages.
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT && humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C - ");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  } else {
    if (temperature == DHT11::ERROR_TIMEOUT || temperature == DHT11::ERROR_CHECKSUM) {
      Serial.print("Temperature Reading Error: ");
      Serial.println(DHT11::getErrorString(temperature));
    }
    if (humidity == DHT11::ERROR_TIMEOUT || humidity == DHT11::ERROR_CHECKSUM) {
      Serial.print("Humidity Reading Error: ");
      Serial.println(DHT11::getErrorString(humidity));
    }
  }

  // Wait for 1 seconds before the next reading.
  delay(5000);

  return 10;
};

void setup() {
  Serial.begin(9600);

  otaMode();         // INIT OTA_MODE
  wifiConnection();  // INIT WIFI_CONNECTION
}

void loop() {
  ArduinoOTA.handle();

  temperatureControl();
}
