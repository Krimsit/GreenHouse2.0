// =========== _ Blue Button _ ===========

void doubleBclick(){
	NORMS[0] = 24;
	NORMS[1] = 0;
	NORMS[2] = 0;
	NORMS[3] = 0;
	EEPROM.write(0, 24);
	EEPROM.write(1, 0);
	EEPROM.write(2, 0);
	EEPROM.write(3, 0);
}

void Bclick(){
	if(!STATE_MODE){
	if( iter_loop / 5000 == 3 ){

		iter_loop = 0;
	}
	else{
		iter_loop = iter_loop / 5000 * 5000 + 5000;
		
	}
	if(!CycleShowInfo(5000, iter_loop)){
		iter_loop = 0;
	}
}}

void BLongPress(){
	Welcome();
}
// =======================================


// ========== _ Yellow Button _ ==========


void YLongPress(){
	// lcd.clear();
 //  lcd.print("Settings:");
	STATE_MODE = !STATE_MODE;
	if(!STATE_MODE){
		lcd.clear();
		switch(iter_loop / 5000){
			case 0:
				setHumidityOnDisplay(getValueSensors("humAir"));break;
			case 1:
				setTempOnDisplay(getValueSensors("tempIn"));break;
			case 2:
				setIdrOnDisplay(getValueSensors("idr"));break;
			case 3: 
				setSoilHumidityOnDisplay(getValueSensors("humSoil"));break;
			default:
			iter_loop = 0;
		}
	}
}

void Yclick(){
	index_mode ++;
	if(index_mode>3){
		index_mode = 0;
	}
}

void doubleYclick(){
	NORMS[index_mode] = valuePot;
	EEPROM.write(index_mode, valuePot);
}
