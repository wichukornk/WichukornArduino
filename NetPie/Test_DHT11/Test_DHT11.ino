#include <ESP8266WiFi.h>
#include "DHT.h"

const char* ssid = "Besten_wifi2.4GHz";
const char* pass = "Bestpass";

#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...  ");  
    Serial.printf("Connection Status: %d\n", WiFi.status()); 
    delay(1000);
  }
  Serial.print("Wi-Fi connected."); 
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  dht.begin();
}
void loop() {
    int humidity = dht.readHumidity();
    int temperature = dht.readTemperature();
    String data = "{\"data\": {\"humidity\":" + String(humidity) + ", \"temperature\":" + String(temperature) + "}}";
    Serial.println(data);
    delay(2000);
}
