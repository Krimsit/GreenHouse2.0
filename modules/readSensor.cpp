int readSensor(){
	//Считываем влажность воздуха
  float h = dht.readHumidity();
  // Считываем температуру Inside
  float t = dht.readTemperature();
  // Считываем температуру Outside
  float At = analogRead(AtPin);
  //расчет освещенности
  int x = analogRead(ldr);
  //reading влажность почвы
  soilSensorValue = analogRead(soilSensorPin);


  int arr[5] = {t, h, At, x, soilSensorValue};

  return arr;
}