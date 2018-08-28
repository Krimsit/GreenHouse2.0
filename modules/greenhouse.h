#include "functions_module.h"

void printDataSensors(int state){
  float h = dht.readHumidity();
   // Считываем температуру Inside
  float t = dht.readTemperature();
  // Считываем температуру Outside
  float At = -273.0;//analogRead(AtPin);
  //расчет освещенности
  float x = (float)analogRead(Idr)/1024.0*100;
  //reading влажность почвы
  float soilSensorValue = (float)analogRead(MoistureOfSoilPin)/1024.0*100;

  if(state == 0){
    Serial.println(h);
    Serial.println(t);
    Serial.println(At);
    Serial.println(x);
    Serial.println(soilSensorValue);  
  }
  
}