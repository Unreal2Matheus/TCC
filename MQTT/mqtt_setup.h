
void mqtt_setup(const char *mqttServer, const int mqttPort, const char *mqttUser, const char *mqtt, const char *mqttPassword, bool wifi)
{ // comecando a comunicacao serial a um baud rate de 115200
    WiFiClient espClient;
    PubSubClient client(espClient);
    client.setServer(mqttServer, mqttPort);
     if (wifi == true)
    {
        while (!client.connected())
        {
            Serial.println("Connecting to MQTT...");

            if (client.connect("ESP32Client", mqttUser, mqttPassword))
            {

                Serial.println("connected");
            }
            else
            {

                Serial.print("failed with state ");
                Serial.print(client.state());
                delay(2000);
            }
        }
    }
}
