//Свет включен
void lightToggle(bool state){
  if(state)
    digitalWrite(RelayLightPin, HIGH);
  else
    digitalWrite(RelayLightPin, LOW);
}

//Температура включена
void tempToggle(bool state){
	if (state)
		digitalWrite(RelayTempPin, HIGH);
	else
		digitalWrite(RelayTempPin, LOW);
}

//Помпа включена
void pompaToggle(bool state){
	if (state)
		digitalWrite(RelayPompaPin, HIGH);
	else
		digitalWrite(RelayPompaPin, LOW);
}


void indGreenToggle(bool state){
	if (state)
		digitalWrite(indGreenPin, HIGH);
	else
		digitalWrite(indGreenPin, LOW);
}

void indRedToggle(bool state){
	if (state)
		digitalWrite(indRedPin, HIGH);
	else
		digitalWrite(indRedPin, LOW);
}

float getValueSensors(String sensor_type){
  if(sensor_type == "tempIn") return dht.readTemperature();
  else if (sensor_type == "humAir") return dht.readHumidity();
  else if (sensor_type == "idr") return (float)analogRead(Idr)/1024.0*100;
  else if (sensor_type == "humSoil") return (float)analogRead(soilSensorPin)/1024.0*100;
  else return -273;
}

void printDataSensors(int state){
	float h = getValueSensors("humAir");
	float t = getValueSensors("tempIn");
	float idr = getValueSensors("idr");
	float soilSensorValue = getValueSensors("humSoil");

	if(state == 0){
		Serial.println(h);
		Serial.println(t);
		Serial.println(idr);
		Serial.println(soilSensorValue);  
	}
}


bool CycleShowInfo(int time_change_info, int iter_loop){
	// time_change_info - in milliseconds
	if( iter_loop % 1000 == 0 ){
		lcd.clear();
		switch(iter_loop / time_change_info){
			case 0: 
				setHumidityOnDisplay(getValueSensors("humAir"));break;
				return HIGH;
			case 1:
				lcd.clear();setTempOnDisplay(getValueSensors("tempIn"));break;
				return HIGH;
			case 2:
				lcd.clear();setIdrOnDisplay(getValueSensors("idr"));break;
				return HIGH;
			case 3: 
				lcd.clear();setSoilHumidityOnDisplay(getValueSensors("humSoil"));break;
				return HIGH;
			default: 
				return LOW;
		}
	}
}

void Settings(String mode){
	lcd.home();
	potMin = 0;
	potMax = 100;
	if(mode == "temp"){
		potMin = 24;
		potMax = 32;
		lcd.print("Settings temp:");
		lcd.setCursor(0, 1);
		lcd.print(NORMS[0]);
		lcd.setCursor(13, 1);
		lcd.print(valuePot);
 	}	

	else if(mode == "humAir"){
		lcd.print("Settings humAir:");
		lcd.setCursor(0, 1);
		lcd.print(NORMS[1]);
		lcd.setCursor(13, 1);
		lcd.print(valuePot);
 	}
 	else if(mode == "Idr"){
 		lcd.print("Settings Idr:");
		lcd.setCursor(0, 1);
		lcd.print(NORMS[2]);
		lcd.setCursor(13, 1);
		lcd.print(valuePot);
 	}
 	else if(mode == "humSoil"){
 		lcd.print("Settings humSoil:");
		lcd.setCursor(0, 1);
		lcd.print(NORMS[3]);
		lcd.setCursor(13, 1);
		lcd.print(valuePot);
 	}

}