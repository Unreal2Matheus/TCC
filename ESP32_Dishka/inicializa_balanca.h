void inicializa_balanca(int DOUT ,int PD_SDK , int scale_p)
{ HX711 scale;
  Serial.println("balanca");
  delay(100);
  Serial.println("Initializing the scale");
  // parameter "gain" is ommited; the default value 128 is used by the library
  // HX711.DOUT  - pin #A1
  // HX711.PD_SCK - pin #A0
  scale.begin(DOUT, PD_SDK);
  scale.tare(); // reset the scale to 0
  scale.set_scale(scale_p);    // this value is obtained by calibrating the scale with known weights; see the README for details
  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale

  }
