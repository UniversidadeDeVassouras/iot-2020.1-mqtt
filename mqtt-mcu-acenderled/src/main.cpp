#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";

WiFiClient espClient;
PubSubClient client(espClient);

const int LED = 2; 

void callback(char* topic, byte* payload, unsigned int length) {
  if(length == 1) {
    if((char)payload[0] == '1') {
      digitalWrite(LED, HIGH);
    }
    else if((char)payload[0] == '0'){
      digitalWrite(LED, LOW);
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Conectando...");
  pinMode(LED, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado!");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
  client.setServer("51.210.110.0", 1883);
  client.setCallback(callback);
  client.connect("1");
  while (!client.connected()) {
    Serial.print("Falha:");
    Serial.print(client.state());
    Serial.println(" nova tentativa em 5 segundos");
    delay(5000);
    client.connect("1");
  }
  Serial.println("Conectado no servidor Mosquitto");
  //client.publish("nodemcu", "Aloha");
  client.subscribe("nodemcu");
}

void loop() {
  client.loop();
}