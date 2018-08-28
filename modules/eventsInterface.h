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
}

void BLongPress(){
	Welcome();
}