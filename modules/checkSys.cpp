/*
	Модуль предназначен для проверки работоспособности системы и логирования каждого шага программы:
		1. Проверка работы всех датчиков, а для начала и их пинов
		2. Логи
		3. Вывод ошибок
*/
void errorShow(int pin){
	digitalWrite(pin, HIGH);
	delay(1000);
	digitalWrite(pin, LOW);
}
void normShow(int pin){
	digitalWrite(pin, HIGH);
	delay(500);
	digitalWrite(pin, LOW);
}
bool SysCheck(int pinGrInd, int pinRedInd, int Pins[4]){
	bool err = false;
	for(int i = 0; i < 4;i++){
		if(i == 3){
			int errValueTemp = 0;
			int errValueHum = 0;

			int valueTemp = Pins[i].readTemperature();
			int valueHum = Pins[i].readHumidity();
			if(valueTemp == errValueTemp || valueHum == errValueHum){
				err = !err;
				Serial.print("error: ", i);
				break;
			}
		}
		else{
			int value = analogRead(Pins[i]);
			if(value == 0 || value == 1024){
				err = !err;
				Serial.print("error: ", i);
				break;
			}
		}
	}


	if(err){
		errorShow(pinRedInd);
		return false;
	}
	else{
		normShow(pinGrInd);
		delay(100);
		normShow(pinGrInd);
		return true;
	}
}