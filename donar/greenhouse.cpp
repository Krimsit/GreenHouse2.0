// Подключаем стандартную библиотеку LiquidCrystal
#include <LiquidCrystal.h>
#include "DHT.h"
// Инициализируем объект-экран, передаём использованные 
// для подключения контакты на Arduino в порядке:
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

#define DHTPIN 3 // номер пина, к которому подсоединен датчик
DHT dht(DHTPIN, DHT11);

int ldr = 0; //и фоторезистора


int soilSensorPin = 1;   
int soilSensorValue = 0; 

const int buttonPin = 2;     // номер входа, подключенный к кнопке



void setup() 
{
    Serial.begin(9600);
    dht.begin();
    // устанавливаем размер (количество столбцов и строк) экрана
    lcd.begin(16, 2);
    // печатаем первую строку
  pinMode(buttonPin, INPUT);   
}


void loop() 
{
  //Считываем влажность
  float h = dht.readHumidity();
  // Считываем температуру
  float t = dht.readTemperature();
  //расчет освещенности
  int x = analogRead(ldr);
  //расчет влажность почвы
  soilSensorValue = analogRead(soilSensorPin);

 
}
