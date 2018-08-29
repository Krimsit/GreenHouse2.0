/*
  0.1. Reaquired libs
*/
#include <DHT.h>
#include <Wire.h>
#include <WireKinetis.h>
#include <LiquidCrystal_SR.h>
#include <OneButton.h>


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

bool first_times = LOW;
int iter_loop    = 4950;

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
  // Ybutton.attachDoubleClick(doubleBclick);
//  Ybutton.attachLongPressStop(YLongPress);


}



int iter_loop_set = 0;


void loop() {
  // lesten writing console (Serial)
  if (Serial.available() > 0) {
    lcd.clear();
    String str = Serial.readString();
    Serial.println(str);

    if (str == "Welcome" or str == "welcome"){
      Welcome();
    }
    else if (str == "Sensor tempIn"){
      CycleShowInfo(1, 1);
    }
    else if (str == "Sensor humAir"){
      CycleShowInfo(1, 2);
    }
    else if (str == "Sensor idr"){
      CycleShowInfo(1, 2);
    }
    else if (str == "Sensor humSoil"){
      CycleShowInfo(1, 3);
    }
    else if (str == "settings"){
      Yclick();
    }
    else if (str == "readHumidity"){
      setHumidityOnDisplay(dht.readHumidity());
    }
    else if (str == "light on"){
       lightToggle(HIGH);
    }
    else if (str == "light off"){
       lightToggle(LOW);
    }
    else if (str == "temp on"){
       tempToggle(HIGH);
    }
    else if (str == "temp off"){
       tempToggle(LOW);
    }
    else if (str == "pompa on"){
       pompaToggle(HIGH);
    }
    else if (str == "pompa off"){
       pompaToggle(LOW);
    }
    else if (str == "green on"){
       indGreenToggle(HIGH);
    }
    else if (str == "green off"){
       indGreenToggle(LOW);
    }
    else if (str == "red on"){
       indRedToggle(HIGH);
    }
    else if (str == "red off"){
       indRedToggle(LOW);
    }
    else{
      lcd.print(str);
    }
  }

//  float arr[5] = {getValueSensors("tempIn"), getValueSensors("humAir"), getValueSensors("idr"), getValueSensors("humSoil"), 0};
  /*
    Функция CheckValuesSensors() будет возращать массив, где элементы 
    будут равняться разнице между настроенной нормой и значением датчиков

    float Diff = CheckValuesSensors(arr) => {3, 0, 300, -100, 0}

    changeDifferenceForSettings(Diff) - предназначен для выполнения и стабилизации разницы значений датциков и норм
      - Diff[0] - разница температур; вклчаем лампочку, пока разница не снизится до нуля
      и тд.

    

  */

// Serial.println(STATE_MODE);
 
 
// else{
//   // Каждые 3 секунды будет вызываться CycleShowInfo
//   

//  if(iter_loop % 3000 == 0){
//    setHumidityOnDisplay(dht.readHumidity());
//  }
  if(STATE_MODE){
//    iter_loop_set = 100;
    if(first_times == HIGH){
      first_times = LOW;
      lcd.clear();
      Settings();
    }
    else{
      Settings();
    }
  } 
  else{
    first_times = LOW;
   if(!CycleShowInfo(5000, iter_loop)){
    iter_loop = 0;
   }
  }
  

  Bbutton.tick();
  Ybutton.tick();

  // =======_cut_========
  int potMin = 20;
  int potMax = 35;

  int valuePot = potMin + (float)round((float)analogRead(2) / 10.24) / 100.0 * (potMax - potMin);

//  Serial.println(valuePot);
  // ====================
  delay(10);
  iter_loop += 10;
  iter_loop_set += 10;
}

