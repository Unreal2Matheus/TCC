int calibra_balanca(int DOUT ,int PD_SDK, int peso_conhecido, HX711 scale)
{ 
  int scale_p
  Serial.println("calibrando a balanca");
  delay(100);
  Serial.println("Initializing the scale");
  // parameter "gain" is ommited; the default value 128 is used by the library
  // HX711.DOUT  - pin #A1
  // HX711.PD_SCK - pin #A0
  scale.begin(DOUT, PD_SDK);
  scale.tare(); // reset the scale to 0
  scale.set_scale();    // this value is obtained by calibrating the scale with known weights; see the README for details
  
  Serial.println("colocar o peso conhecido dentro de 5 seg");
  scale_p = scale.get_units(10)/peso_conhecido;
  return scale_p
  }
