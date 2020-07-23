#include <Arduino.h>
#include <DHT.h>
#include <Wifi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";

WiFiClient espClient;
PubSubClient client(espClient);

DHT dht(4,DHT11);

void setup() {
  Serial.begin(9600);
  Serial.println("Testando");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.print("...");
  }
  Serial.println(WiFi.localIP());
  client.setServer("51.210.110.0", 1883);
  client.connect("1");
  while (!client.connected()) {
    Serial.print(client.state());
    Serial.print("Falha na conexão");
    delay(2000);
    client.connect("1");
  }
  Serial.println("Servidor do Grande Mosquitão");
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float temp = dht.readTemperature();
  client.publish("Temperatura", String(temp).c_str());
  client.publish("Umidade", String(h).c_str());
}