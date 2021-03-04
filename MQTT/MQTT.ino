#include <WiFi.h>
#include <PubSubClient.h>
#include "wi_fi_setup.h"
#include "mqtt_setup.h"
// primeiro fazemos um hardcoding para receber o nome da rede e a senha
// TODO mudar para receber ssid e password do app
const char* ssid = "Sala_oliveira";
const char* password =  "juca1923";
// o servidor mqtt n ira mudar logo ele pode ser hardcoded
const char* mqttServer = "farmer.cloudmqtt.com";
const int mqttPort =  14098;
const char* mqttUser = "zfdpgatg";
const char* mqttPassword = "QqNg-ir0-N_M";
#define topic "spot/Balanca" // define o topico que ira ser publicado os dados 
#define debug_topic "spot/debug"   
bool debug = true;             //Display log message if True
char data[80];



/* definitions for deepsleep */
//#define uS_TO_S_FACTOR 1000000        /* Conversion factor for micro seconds to seconds */
//#define TIME_TO_SLEEP 180              /* Time ESP32 will go to sleep for 5 minutes (in seconds) */


void setup() {// comecando a comunicacao serial a um baud rate de 115200
  Serial.begin(115200);

}
float t = 0;
String h= "APA";
 bool wifi;
void loop()
{ 
  wifi = wi_fi_setup(ssid, password);
  mqtt_setup(mqttServer, mqttPort, mqttUser, mqttPassword,wifi);
  t = t+1.32;  
  String dhtReadings = "{\"peso\":\"" + String(t) + "\", \"cerveja\":\"" + h + "\"}";
  dhtReadings.toCharArray(data, (dhtReadings.length() + 1));
  // Publish values to MQTT topics
  client.publish(topic, data);   // Publish readings on topic (glasshouse/dhtreadings)
  if ( debug ) 
  {  
      Serial.println("Readings sent to MQTT.");
  }
  Serial.println(WiFi.status() == WL_CONNECTED );
  Serial.println(client.connected());
  if (client.connected()==0) {
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
  }
  if (WiFi.status() !=  WL_CONNECTED )
  { wi_fi_setup(ssid,password);
    }
  
  delay(6000);
  

}
