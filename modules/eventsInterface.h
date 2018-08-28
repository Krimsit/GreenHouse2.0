void doubleBclick(){
	// static int m = LOW;
	// m = !m;
	Serial.println("Double Click!");
	lcd.clear();
	lcd.print("DoubleClick!");
}
void Bclick(){
	Serial.println("Click!");
	lcd.clear();
	lcd.print("Click!");
	if(!CycleShowInfo(5000, (iter_loop % 5000) + 1000)){
		iter_loop = 0;
	}
}

void BLongPress(){
	Welcome();
}