/*
	Модуль предназначен для проверки работоспособности системы и логирования каждого шага программы:
		1. Проверка работы всех датчиков, а для начала и их пинов
		2. Логи
		3. Вывод ошибок
*/
void grindon(int pin){
	digitalWrite(pin, HIGH);
}
void grindoff(int pin){
	digitalWrite(pin, LOW);
}
void CheckSys(int pinGrInd, int pinRedInd){
	// пока здесь нет условия, но оно вскоре повится(но это не точно), а пока здесь просто будет
	// будет мигать, а потом просто гореть зеленый индикатор)
	for(int i = 0; i < 5; i++){
		grindon(pinGrInd);
		delay(500);
		grindoff(pinGrInd);
		delay(500);
	}
	grindon(pinGrInd);
}