// =========== _ Blue Button _ ===========

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
	// if(!CycleShowInfo(5000, (iter_loop % 5000) + 1000)){
	// 	iter_loop = 0;
	// }
}

void BLongPress(){
	Welcome();
}
// =======================================


// ========== _ Yellow Button _ ==========


void Yclick(){
	first_times = HIGH;
	// lcd.clear();
 //  lcd.print("Settings:");
	STATE_MODE = !STATE_MODE;
	if(!STATE_MODE){
		lcd.clear();
		switch(iter_loop / 5000){
			case 1: 
				setHumidityOnDisplay(getValueSensors("humAir"));break;
			case 2:
				setTempOnDisplay(getValueSensors("tempIn"));break;
			case 3:
				setIdrOnDisplay(getValueSensors("idr"));break;
			case 4: 
				setSoilHumidityOnDisplay(getValueSensors("humSoil"));break;
		}
	}
}
