//Свет включен
void lightOn(){
  digitalWrite(RelayLight, HIGH);
}

//Свет выключен
void lightOff(){
  digitalWrite(RelayLight, LOW);
}

//Температура включена
void tempOn(){
  digitalWrite(RelayTemp, HIGH);
}

//Температура включена
void tempOff(){
  digitalWrite(RelayTemp, LOW);
}

//Помпа включена
void pompaOn(){
  digitalWrite(RelayPompa, HIGH);
}


//Помпа включена
void pompaOff(){
  digitalWrite(RelayPompa, LOW);
}



// Вывод на дисплэй значения с датчиков

void setHumidityOnDisplay(int h){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.setCursor(14, 0);
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("Norm: ");
  
  if(h < 40){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h > 40 && h < 60){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h > 60){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}

void setTempOnDisplay(int h){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(14, 0);
  lcd.print(h);

 lcd.setCursor(0, 1);
 lcd.print("Norm: ");
  
  if(h < 17){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h > 17 && h < 24){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h > 24){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}

void setIdrOnDisplay(int h){
lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ill-tion:  ");
  lcd.setCursor(13, 0);
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("Norm: ");
  
  if(h < 300){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h > 300 && h < 500){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h > 500){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}

//Влажность почвы
void setSoilHumidityOnDisplay(int h){
lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SoilHum-ty: ");
  lcd.setCursor(13, 0);
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("Norm: ");
  
  if(h < 350){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h > 350 && h < 600){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h > 600){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}



void Welcome(){
  //  Welcome
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("GreenHouse 2.0");

  delay(2500);
  lcd.clear();

  //  Author 
  lcd.setCursor(0, 0);
  lcd.print("Author: ");
  lcd.setCursor(0, 1);
  lcd.print("Shenyagin D.");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Co-Author: ");
  lcd.setCursor(0, 1);
  lcd.print("Lukyanov A.");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Co-Author: ");
  lcd.setCursor(0, 1);
  lcd.print("Subbotin A.");

  delay(2000);
  lcd.clear();

  //  Scientific director
  lcd.setCursor(0, 0);
  lcd.print("Scientific dir.:");
  lcd.setCursor(0, 1);
  lcd.print("Kraev N.V.");

  delay(3000);
  lcd.clear();
}
