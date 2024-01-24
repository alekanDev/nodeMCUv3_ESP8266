
//PROJECT BASE TO NODEMCU V3 (ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

ESP8266WiFiMulti wifiMulti;
byte cont = 0;
byte max_intentos = 50;
const uint32_t connectTimeoutMS = 5000;


void setup() {
  Serial.begin(9600);
  Serial.println("\n");

  wifiMulti.addAP("SSID", "PASSWORD*");

  while (WiFi.status() != WL_CONNECTED and cont < max_intentos) {
    cont++;
    delay(500);
    Serial.print(".");
  }

  ArduinoOTA.setHostname("HOSTNAME");  // IS THE BOARD NAME
  ArduinoOTA.setPassword("PASSWORD");  // IS SECRET PASS TO CONNECTION
  ArduinoOTA.setPort("PORT"); // PORT IS NUMERIC VALUE

  ArduinoOTA.begin();

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
}

void loop() {
  ArduinoOTA.handle();
}
