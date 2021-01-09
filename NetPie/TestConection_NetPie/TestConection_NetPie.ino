#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Besten_wifi2.4GHz";
const char* password = "Bestpass";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "2c6563ec-ba7f-49a9-bcac-4ca69d1a2326";
const char* mqtt_username = "6uQEqCf7GSybeUFKBDjq8hm8urSJ53co";
const char* mqtt_password = "o9akb*H)1-72BYS8CL1f1MGkWmS4FBBE";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
int value = 0;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    client.publish("@msg/test", "Hello NETPIE2020");
    Serial.println("Hello NETPIE2020");
  }
  delay(1); 
}
