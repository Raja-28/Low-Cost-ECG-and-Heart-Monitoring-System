#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
#define WIFISSID "***********"                                // Put your WifiSSID here
#define PASSWORD "***********"                                 // Put your wifi password here
#define TOKEN "BBFF-YKxITsj1YPeTMxw7mq8lvYFBpXnCxD"         // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "myecgsensor"                       // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 
                                                            //it should be a random and unique ascii string and different from all other devices

#define VARIABLE_LABEL "myecg" // Assing the variable label
#define DEVICE_LABEL "esp8266" // Assig the device label
 
#define SENSOR A0 // Set the A0 as SENSOR
 
char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
// Space to store values to send
char str_sensor[10];

WiFiClient ubidots;
PubSubClient client(ubidots);
 
void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.write(payload, length);
  Serial.println(topic);
}
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}