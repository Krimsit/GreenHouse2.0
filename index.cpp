/*
	0.1. Reaquired libs
*/
// Will replace lib on lib@i2c
// work with display on i2c
#include <LiquidCrystal.h>
// work with DHT (датчик влажности и температуры)
#include "DHT.h"

//-------------------------------------------------------------------------------

/*
	0.2. Init vars for work with sensors and indicators
*/

// Инициализируем объект-экран, передаём использованные 
// для подключения контакты на Arduino в порядке:
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

#define DHTPIN 3 								// номер пина, к которому подсоединен датчик
DHT dht(DHTPIN, DHT11);

// Pins

const int ldr = 0; 							//пин фоторезистора

// Влажность почвы
const int soilSensorPin   = 1;	//Значение пина датчика влажности почвы
const int soilSensorValue = 0;	//Временне значение датчика вложносит почвы

const int tempInPin = 10;				//Пин датчика температуры внутри теплицы

// Кнопки
const int YbuttonPin = 9;				// номер пина желтой кнопки
const int BbuttonPin = 13; 			// номер пина голобой кнопки

// relaies
const int tempPin  = 2;					//Пин рэле с лампочкой
const int lightPin = 3;					//Пин рэле с светодиодной панелью
const int waterPin = 4;					//Пин рэле с помпой

// Indicators
const int indRedPin  = 7;				//Пин красного индикатора
const int indGreePin = 8;				//Пин красного индикатора

// krutilra(potentiometer)
const int potPin = 0;						//Пин потециометра(крутилки)(A0)


// ------------------------------------------------------------------------------

// Copy-past next down includes files (!)
/*
	1.0 Welcome block (main function)
*/

// Welcome product
#include "modules/Welcome.cpp"

/*
	1.1 Chack Sys (Pre-function)
*/
#include "modules/checkSys.cpp"

// ------------------------------------------------------------------------------

/*
	Main part programm
*/
void setup(){
	// Init
	// begining Console on 9600 port
	Serial.begin(9600);

	// init dht
	dht.begin();

	// устанавливаем размер (количество столбцов и строк) экрана
	lcd.begin(16, 2);

	// init pins mode for sensors and indicators
  pinMode(buttonPin, INPUT);

  // main run functions
  Welcome();
  SysCheck();
}

int ModState = 0;
void loop(){
	int buttonState = digitalRead(buttonPin);
}