void BlueButClick(int buttonPin, int STATE){

	int buttonState = digitalRead(buttonPin);

  if (buttonState == 0){
  	switch(STATE){
  		case 0: {
				lcd.clear();
				setTempOutSideOnDisplay(readSensor()[0]);
  		}break;

  		case 1: {
				lcd.clear();
				setHumidityOnDisplay(readSensor()[1]);
  		}break;

  		case 2: {
				lcd.clear();
				setTempInSideOnDisplay(readSensor()[2]);
  		}break;


  		case 3: {
				lcd.clear();
				setIdrOnDisplay(readSensor()[3]);
  		}break;

  		case 4: {
				lcd.clear();
				setSoilHumidityOnDisplay(readSensor()[4]);
  		}break;
  		
  		default:{
				if(STATE > 3){
					STATE = 0;
				}
				else{
					STATE++;
				}
				Serial.println(STATE);
			}
  	}
  }
  else{
    
  }
}