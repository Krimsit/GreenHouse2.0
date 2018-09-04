/*
  0.1. Reaquired libs
*/
#include <DHT.h>
#include <Wire.h>
#include <WireKinetis.h>
#include <LiquidCrystal_SR.h>
#include <OneButton.h>
#include <EEPROM.h>


// -----------------------------------------------------------------------------------------


/*
  0.2. Init vars for work with sensors and indicators
*/

// Display init
LiquidCrystal_SR lcd(6, 5, 9);

// temperature and humidity sensor
#define DHTPIN 10
DHT dht(DHTPIN, DHT11);



// soil Sensor
const int soilSensorPin = 0;    //Значение пина датчика влажности почвы

// Photoresister 
const int Idr           = 1;    //пин фоторезистора

// relaies
const int RelayPompaPin = 2;    //Пин рэле с помпой
const int RelayTempPin  = 3;    //Пин рэле с лампочкой
const int RelayLightPin = 4;    //Пин рэле с светодиодной панелью

// Buttons
const int buttonPinMode = 8;    // номер пина желтой кнопки
const int buttonPinInfo = 11;   // номер пина голубой кнопки

// Indicators
const int indGreenPin   = 13;   // номер пина зеленого индикатора(светодиода)
const int indRedPin     = 12;   // номер пина красного индикатора(светодиода)

// krutilra(potentiometer)
const int potPin        = 2;    //Пин потециометра(крутилки)(A0)

// Tempetature outside
const int tempOutPin    = -1;   //Пин датчика температуры снаружи теплицы

// Configs
bool STATE_MODE         = LOW;  //Состояние режима настроек

int iter_loop    = 0;
int potMin;
int potMax;
float NORMS[4] = {24, 0, 0, 0};
String mode[4] = {"temp", "humAir", "Idr", "humSoil"};
int index_mode = 0;
int valuePot;
float sensors[4];

// Попробовать перенести в начало дока (!)
#include <greenhouse.h>


// init buttons
OneButton Bbutton(buttonPinInfo, true);
OneButton Ybutton(buttonPinMode, true);
// -----------------------------------------------------------------------------------------

/*
  Main part
*/



void setup(){
  Serial.begin(9600);   // beginig console on 9600 port

  lcd.begin(16,2);      // Initializing LCD
  lcd.home();           // begin lcd (0,0)

  dht.begin();          // begin dht

  /*
    init pins
  */

  //  Pin MOds to relay
  pinMode(RelayLightPin, OUTPUT);
  pinMode(RelayTempPin, OUTPUT);
  pinMode(RelayPompaPin, OUTPUT);

  pinMode(soilSensorPin, INPUT);

  pinMode(buttonPinInfo, INPUT_PULLUP);
  pinMode(buttonPinMode, INPUT_PULLUP);

  digitalWrite(buttonPinInfo, HIGH);
  digitalWrite(buttonPinMode, HIGH);

  // digitalWrite(indGreenPin, HIGH);


  Bbutton.attachClick(Bclick);
  Bbutton.attachDoubleClick(doubleBclick);
  Bbutton.attachLongPressStop(BLongPress);

  Ybutton.attachClick(Yclick);
  Ybutton.attachDoubleClick(doubleYclick);
  Ybutton.attachLongPressStop(YLongPress);

  for(int i = 0; i<4;i++){
    if(EEPROM.read(i)!=255){
    NORMS[i] = EEPROM.read(i);
    }
  }
  iter_loop = 0;
}

float sensors_change[4];
void loop() {
 //Serial.println(STATE_MODE); 
  if (Serial.available() > 0) {
    lcd.clear();
    String str = Serial.readString();
    Serial.println(str);

    if (str == "welcome"){
      Welcome();
    }
    else if (str == "Yclick"){
      Yclick();
    }
    else if (str == "doubleYclick"){
      doubleYclick();
    }
    else if (str == "YLongPress"){
      YLongPress();
    }
    else if (str == "Bclick"){
      Bclick();
    }
    else if (str == "doubleBclick"){
      doubleBclick();
    }
    else if (str == "BLongPress"){
      YLongPress();
    }
  }
//    else if (str == "light on"){
//       lightToggle(HIGH);
//    }
//    else if (str == "light off"){
//       lightToggle(LOW);
//    }
//    else if (str == "temp on"){
//       tempToggle(HIGH);
//    }
//    else if (str == "temp off"){
//       tempToggle(LOW);
//    }
//    else if (str == "pompa on"){
//       pompaToggle(HIGH);
//    }
//    else if (str == "pompa off"){
//       pompaToggle(LOW);
//    }
//    else{
//      lcd.print(str);
//    }
//  }

  sensors[0] = getValueSensors("tempIn");
  sensors[1] = getValueSensors("humAir");
  sensors[2] = getValueSensors("idr");
  sensors[3] = getValueSensors("humSoil");
  
  valuePot = potMin + (float)round((float)analogRead(2) / 10.24) / 100.0 * (potMax - potMin);
  if(STATE_MODE){
    if(iter_loop % 100 == 0){
      if(iter_loop > 20000){
        iter_loop = 0;
      }
      lcd.clear();
      Settings(mode[index_mode]);
    }
  } 
   else if(!CycleShowInfo(5000, iter_loop)){
    iter_loop = -10;
   }

  for(int i = 0; i<4; i++){   
    sensors_change[i] = NORMS[i] - sensors[i]; 
  }

  if(!STATE_MODE){
  if(sensors_change[0] > 0){
     tempToggle(HIGH);
  }
  else{
    tempToggle(LOW);
  }
  if(sensors_change[2] > 0){
     lightToggle(HIGH);
  }
  else{
    lightToggle(LOW);
  }
  if(sensors_change[3] > 0){
     pompaToggle(HIGH);
  }
  else{
    pompaToggle(LOW);
  }
  }
  else{
    tempToggle(LOW);
    lightToggle(LOW);
    pompaToggle(LOW);
  }
  
  Bbutton.tick();
  Ybutton.tick();

  delay(10);
    iter_loop += 10;
  }


