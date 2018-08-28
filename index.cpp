#include <DHT.h>
#include <Wire.h>
#include <WireKinetis.h>
#include <LiquidCrystal_SR.h>


LiquidCrystal_SR lcd(6, 5, 9);

#define DHTPIN 10 // номер пина, к которому подсоединен датчик
DHT dht(DHTPIN, DHT11);

//Реле
int RelayLight = 4;
int RelayTemp = 3;
int RelayPompa = 2;

//Экран
int Idr = 1;

const int MoistureOfSoilPin = 0;  //Значение пина датчика влажности почвы
int soilSensorValue = 0;  //Временное значение датчика вложносит почвы

//Кнопки
int buttonPinInfo = 11;
int buttonPinMode = 8;

int ind1 = 13;

#include <greenhouse.h>

#include <OneButton.h>

OneButton Bbutton(buttonPinInfo, true);


void setup(){
  Serial.begin(9600);
  
  lcd.begin(16,2);               // Initializing LCD
  lcd.home ();
  
  dht.begin();
//  Pin MOds to relay
  pinMode(RelayLight, OUTPUT);
  pinMode(RelayTemp, OUTPUT);
  pinMode(RelayPompa, OUTPUT);
  
  pinMode(MoistureOfSoilPin, INPUT);
  
  pinMode(buttonPinInfo, INPUT_PULLUP);
  pinMode(buttonPinMode, INPUT_PULLUP);
 
  digitalWrite(buttonPinInfo, HIGH);
  digitalWrite(buttonPinMode, HIGH);
//  lightOn();
//  tempOn();
  digitalWrite(ind1, HIGH);

  
  Bbutton.attachDoubleClick(doubleBclick);
  Bbutton.attachClick(Bclick);
}
void doubleBclick(){
  static int m = LOW;
  // reverse the LED 
  m = !m;
  Serial.println("Double Click!");
}
void Bclick(){
  static int m = LOW;
  // reverse the LED 
  m = !m;
  Serial.println("Click!");
}

int STATE = 0;
int i = 0;
String str = "";

void loop() {
    if (Serial.available() > 0) {
        lcd.clear();
        String str = Serial.readString();
        Serial.println(str);
        if (str == "Welcome" or str == "welcome"){
          Welcome();
        }
        else if (str == "readSensors"){
          printDataSensors(0);
        }
        else{
          lcd.print(str);
        }
    }

  Bbutton.tick();
  delay(10);
}

  
//Serial.println(17 / (int)round((float)analogRead(2) / 10.0) + 28);
//delay(20);


