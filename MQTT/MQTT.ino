#include <WiFi.h>
#include <PubSubClient.h>
#include "wi_fi_setup.h"
// primeiro fazemos um hardcoding para receber o nome da rede e a senha
// TODO mudar para receber ssid e password do app
const char *ssid = "Sala_oliveira";
const char *password = "juca1923";
// o servidor mqtt n ira mudar logo ele pode ser hardcoded
const char *mqttServer = "farmer.cloudmqtt.com";
const int mqttPort = 14098;
const char *mqttUser = "zfdpgatg";
const char *mqttPassword = "QqNg-ir0-N_M";
#define topic "spot/Balanca"
#define debug_topic "spot/debug"
bool debug = true; //Display log message if True
char data[80];
float peso = 0;
String cerveja = "APA";
/* definitions for deepsleep */
#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 30      /* Time ESP32 will go to sleep for 5 minutes (in seconds) */

WiFiClient espClient;
PubSubClient client(espClient);
// testa se o ESP32 esta conectado com o WIFI
bool isWiFiConnected (){
  return WiFi.status() == WL_CONNECTED; 
}
// testa se o ESP32 esta conecatado com o servidor MQTT
bool isMQTTConnected (){
  return client.connected();
}
// tenta se conectar com o servidor MQTT
void attemptConnectMQTT(){
  Serial.println("Connecting to MQTT...");

  if (client.connect("ESP32Client", mqttUser, mqttPassword))
  {

    Serial.println("connected");
  }
  else
  {

    Serial.print("failed with state ");
    Serial.print(client.state());
    Serial.println(isWiFiConnected());
  }
}
// coloca o ESP32 num estado de baixo gasto de energia
void Slepping(){

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR); //go to sleep
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
  Serial.println("Going to sleep as normal now.");
  esp_deep_sleep_start();
}

void setup()
{ // comecando a comunicacao serial a um baud rate de 115200
  Serial.begin(115200);

  wi_fi_setup(ssid, password);
  client.setServer(mqttServer, mqttPort);
  // tenta conectar com o mqtt caso o WIFI tambem esteja conectado 
  while (!isMQTTConnected() && isWiFiConnected())
  {
    attemptConnectMQTT();
  }
}
bool publicou;
int counter;
void loop()
{ 
  peso = peso + 1.32;
  // cria a  mensagem a ser publicada no formato json
  String HX711Readings = "{\"peso\":\"" + String(peso) + "\", \"cerveja\":\"" + cerveja + "\"}";
  HX711Readings.toCharArray(data, (HX711Readings.length() + 1));

  // publica os valores para o topico MQTT
  publicou = client.publish(topic, data,true);
  // checa se pulicou e depois da quinta publicação bota o esp em modo sleep
  if (publicou)
  {
    Serial.println("Readings sent to MQTT.");
    Serial.println(publicou);
    counter = counter+1;
    if(counter==5){
      Slepping();
    }
    
  }
  // tenta a reconexão com o wifi e o servidor mqtt caso a publicação tenha falhado
  else {
    counter = 0;
    Serial.println(isWiFiConnected());
    Serial.println(isMQTTConnected());
    if (!isWiFiConnected()){
      wi_fi_setup(ssid, password);
    }
    else if (!isMQTTConnected())
    {
      while (!isMQTTConnected() && isWiFiConnected())
      { 
        attemptConnectMQTT();
        delay(2000);
      }
    }  
  }
 
delay(6000);
}
