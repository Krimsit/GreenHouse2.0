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