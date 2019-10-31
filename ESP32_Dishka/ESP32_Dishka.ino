#include "HX711.h"
#include <WiFi.h>
#include <PubSubClient.h>
const char* ssid = "yourNetworkName";
const char* password =  "yourNetworkPassword";
const char* mqttServer = "m11.cloudmqtt.com";
const int mqttPort = 12948;
const char* mqttUser = "yourMQTTuser";
const char* mqttPassword = "yourMQTTpassword";
const int DOUT = 25; // pino do ESP32 que entra DOUT
const int PD_SCK = 26; // pino do ESP32 que entra PD_SCK
const int peso_conhecido;
const int scale_p = -21974.1452; // parametro usado na classe scale
 
WiFiClient espClient;
PubSubClient client(espClient);

#include "inicializa_balanca.h"
#include "loop_balanca.h";
HX711 scale;



void setup() {
  Serial.begin(115200);
  Serial.println("Initializing the scale");
  // parameter "gain" is ommited; the default value 128 is used by the library
  // HX711.DOUT	- pin #A1
  // HX711.PD_SCK	- pin #A0
  inicializa_balanca(DOUT, PD_SCK, scale_p); // vai printar as leituras ADC da balanca , onde o read e a leitura pura do ADC,
                                    //o value e a leitura menos o peso da tara , e unit o valor apos tirar o peso da tara e aplicar o fator scale 
 //calibra_balanca( DOUT , PD_SDK,  peso_conhecido);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP32");
 

}

void loop() {
 void loop_balanca();
 client.loop();

}
 
 
