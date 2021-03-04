  bool wi_fi_setup(const char*ssid, const char*password)
  {  
  Serial.printf("Wi-Fi mode set to WIFI_STA %s\n", WiFi.mode(WIFI_STA) ? "" : "Failed!");
  while (WiFi.status() != WL_CONNECTED) {
  WiFi.begin(ssid, password);
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  return WiFi.status() == WL_CONNECTED;
  }
