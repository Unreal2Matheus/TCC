 void loop_balanca()
  {HX711 scale;
//  Serial.print("one reading:\t");
//  Serial.print(scale.get_units(), 1);
//  Serial.print("\t| average:\t");
// o get_units ira pritar um valor medio apos os devidos ajustes de tara e scale onde o tanto de valores que entram na media aritmetica 
// e dentro do () e o valor depois da virgula a precisao das casas decimais
  Serial.println(scale.get_units(10), 1);
  }
