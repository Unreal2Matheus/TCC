 void loop_balanca()
  {HX711 scale;
//  Serial.print("one reading:\t");
//  Serial.print(scale.get_units(), 1);
//  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);
  }
