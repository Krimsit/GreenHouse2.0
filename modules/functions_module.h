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

void printDataSensors(int state){
	float h = dht.readHumidity();
	float t = dht.readTemperature();
	float At = -273.0;
	float x = (float)analogRead(Idr)/1024.0*100;
	float soilSensorValue = (float)analogRead(soilSensorPin)/1024.0*100;

	if(state == 0){
		Serial.println(h);
		Serial.println(t);
		Serial.println(At);
		Serial.println(x);
		Serial.println(soilSensorValue);  
	}
}