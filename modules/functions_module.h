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
	if( iter_loop % time_change_info == 0 ){
		switch(iter_loop / time_change_info){
			case 1: 
				setHumidityOnDisplay(getValueSensors("humAir"));break;
				return HIGH;
			case 2:
				setTempOnDisplay(getValueSensors("tempIn"));break;
				return HIGH;
			case 3:
				setIdrOnDisplay(getValueSensors("idr"));break;
				return HIGH;
			case 4: 
				setSoilHumidityOnDisplay(getValueSensors("humSoil"));break;
				return HIGH;
			default: 
				return LOW;
		}
		// change info
	}
	else{
		return HIGH;
	}

}

void Settings(){
	lcd.home();
	lcd.print("Settings: ");
}