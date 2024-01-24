//PROJECT BASE TO NODEMCU V3 (ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "sensitiveData.h"

ESP8266WiFiMulti wifiMulti;
byte cont = 0;
byte max_intentos = 50;
const uint32_t connectTimeoutMS = 5000;


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
  ArduinoOTA.setHostname(OTA_host);  // IS THE BOARD NAME
  ArduinoOTA.setPassword(OTA_pass);  // IS SECRET PASS TO CONNECTION
  ArduinoOTA.setPort(OTA_port);      // PORT IS NUMERIC VALUE

  ArduinoOTA.begin();
  return 1;
};

void setup() {
  Serial.begin(9600);

  otaMode();         // INIT OTA_MODE
  wifiConnection();  // INIT WIFI_CONNECTION
}

void loop() {
  ArduinoOTA.handle();
}
