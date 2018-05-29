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

void setHumidityOnDisplay(int h){

  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.setCursor(14, 0);
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("Norm: ");
  
  if(h < 40){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h > 40 && h < 60){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h > 60){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}

void setTempOnDisplay(int h){

  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(14, 0);
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("Norm: ");
  
  if(h < 17){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h > 17 && h < 24){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h > 24){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}

void setIdrOnDisplay(int h){

  lcd.setCursor(0, 0);
  lcd.print("Ill-tion:  ");
  lcd.setCursor(13, 0);
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("Norm: ");
  
  if(h < 300){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h > 300 && h < 500){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h > 500){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}

void setSoilHumidityOnDisplay(int h){

  lcd.setCursor(0, 0);
  lcd.print("SoilHum-ty: ");
  lcd.setCursor(13, 0);
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("Norm: ");
  
  if(h < 350){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h > 350 && h < 600){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h > 600){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}

void setup() 
{
    Serial.begin(9600);
    dht.begin();
    // устанавливаем размер (количество столбцов и строк) экрана
    lcd.begin(16, 2);
    // печатаем первую строку
  pinMode(buttonPin, INPUT);   
}

int STATE = 0;
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

  int buttonState = digitalRead(buttonPin);
  if (buttonState == 0){
    if(STATE == 0){
       lcd.clear();
       setTempOnDisplay(t);
    }
    else if (STATE == 1){
        lcd.clear();
      setHumidityOnDisplay(h);
    }
    else if (STATE == 2){
        lcd.clear();
      setIdrOnDisplay(x);
    }
    else if (STATE == 3){
      lcd.clear();
      setSoilHumidityOnDisplay(soilSensorValue);
    }
  }
  else{
    if(STATE > 3){
      STATE = 0;
    }
    else{
      STATE++;
  }
    Serial.println(STATE);
  }
  
  // устанавливаем курсор в колонку 0, строку 1. То есть на
  // самом деле это вторая строка, т.к. нумерация начинается с нуля
  delay(100);
}
