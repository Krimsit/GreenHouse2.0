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
const int soilSensorPin	= 0;		//Значение пина датчика влажности почвы

// Photoresister 
const int Idr 					= 1; 		//пин фоторезистора

// relaies
const int RelayPompaPin = 2;		//Пин рэле с помпой
const int RelayTempPin  = 3;		//Пин рэле с лампочкой
const int RelayLightPin = 4;		//Пин рэле с светодиодной панелью

// Buttons
const int buttonPinMode = 8; 		// номер пина голобой кнопки
const int buttonPinInfo = 11;		// номер пина желтой кнопки

// Indicators
const int indGreenPin 	= 13;		// номер пина зеленого индикатора(светодиода)
const int indRedPin 		= -1;		// номер пина красного индикатора(светодиода)

// krutilra(potentiometer)
const int potPin 				= 2;		//Пин потециометра(крутилки)(A0)

// Tempetature outside
const int tempOutPin 		= -1;		//Пин датчика температуры снаружи теплицы

// Configs
bool STATE_MODE 				= false;//Состояние режима настроек


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
	Serial.begin(9600);		// beginig console on 9600 port

	lcd.begin(16,2);			// Initializing LCD
	lcd.home();						// begin lcd (0,0)

	dht.begin();					// begin dht

	/*
		init pins
	*/

	//  Pin MOds to relay
	pinMode(RelayLight, OUTPUT);
	pinMode(RelayTemp, OUTPUT);
	pinMode(RelayPompa, OUTPUT);

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
	// Ybutton.attachLongPressStop(BLongPress);
}


String str = "";
int iter_loop = 10; // not 0 or changed	(!)

void loop() {
	// lesten writing console (Serial)
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

	float arr[5] = {getValueSensors("tempIn"), getValueSensors("humAir"), getValueSensors("idr"), getValueSensors("humSoil"), 0};
	/*
		Функция CheckValuesSensors() будет возращать массив, где элементы 
		будут равняться разнице между настроенной нормой и значением датчиков

		float Diff = CheckValuesSensors(arr) => {3, 0, 300, -100, 0}

		changeDifferenceForSettings(Diff) - предназначен для выполнения и стабилизации разницы значений датциков и норм
			- Diff[0] - разница температур; вклчаем лампочку, пока разница не снизится до нуля
			и тд.

		

	*/


	if(STATE_MODE){
		// Settings
		lcd.clear();
		lcd.print("Settings");
	}
	else{
		// Каждые 3 секунды будет вызываться CycleShowInfo
		if(!CycleShowInfo(5000, iter_loop)){
			iter_loop = 0;
		}
	}
	


	Bbutton.tick();

	// =======_cut_========
	int potMin = 20;
	int potMax = 35;

	int valuePot = potMin + (float)round((float)analogRead(2) / 10.24) / 100.0 * (potMax - potMin);

	Serial.println(valuePot);
	// ====================
	delay(10);
	iter_loop += 10;
}

