
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <MQTT.h>
#define BUFFER_SIZE 100


const char *ssid =  "BTHub6-GP2X";    // cannot be longer than 32 characters!
const char *pass =  "TLdRFAHymPW6";   //


void callback(const MQTT::Publish& pub) {
  Serial.println(pub.payload_string());
  if (pub.payload_string() == "1") {
    digitalWrite(14, HIGH);
  }
  else {
    digitalWrite(14, LOW);
  }
}

WiFiClient wclient;
PubSubClient client(wclient, "m21.cloudmqtt.com", 18694);

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(12, OUTPUT);
}



void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.printf("Connecting to ");
    Serial.printf(ssid);
    Serial.println("...");
    WiFi.begin(ssid, pass);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    Serial.println("WiFi connected");

  }
  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      if (client.connect(MQTT::Connect("arduinoClient")
                         .set_auth("scknjdou", "d44gkmL5YXx5"))) {
        Serial.println("Connected to MQTT server");
        client.set_callback(callback);
        client.subscribe("test/Topic");
        client.publish("test/Topic2", "SENT");

      }
    }

    if (client.connected())
      client.loop();
  }

}

