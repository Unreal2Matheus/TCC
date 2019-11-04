#include "HX711.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "inicializa_balanca.h"
#include "loop_balanca.h";
#include "wi_fi_setup.h"
const char* ssid = "Oliveira";
const char* password =  "juca1923";
const char* mqttServer = "farmer.cloudmqtt.com";
const int mqttPort =  14098;
const char* mqttUser = "zfdpgatg";
const char* mqttPassword = " QqNg-ir0-N_M";
const int DOUT = 25; // pino do ESP32 que entra DOUT
const int PD_SCK = 26; // pino do ESP32 que entra PD_SCK
const int peso_conhecid=0;
const int scale_p = -21974.1452; // parametro usado na classe scale
 
WiFiClient espClient;
PubSubClient client(espClient);


HX711 scale;



void setup() {
  Serial.begin(115200);

  // parameter "gain" is ommited; the default value 128 is used by the library
  // HX711.DOUT	- pin #A1
  // HX711.PD_SCK	- pin #A0
  inicializa_balanca(DOUT, PD_SCK, scale_p); // vai printar as leituras ADC da balanca , onde o read e a leitura pura do ADC,
                                    //o value e a leitura menos o peso da tara , e unit o valor apos tirar o peso da tara e aplicar o fator scale 
 //calibra_balanca( DOUT , PD_SDK,  peso_conhecido);

 wi_fi_setup(ssid,password);

 
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
  client.loop();

  
}
 
 
