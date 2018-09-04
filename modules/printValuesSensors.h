// Вывод на дисплэй значения с датчиков

void setHumidityOnDisplay(int h){
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");

  lcd.setCursor(16-String(h).length(), 0);
  lcd.print(h);

  lcd.setCursor(0, 1);
  lcd.print("Norm: ");
  
  if(h < 40){
    lcd.setCursor(12, 1);
    lcd.print(" MIN");
  }
  else if(h >= 40 && h < 60){
    lcd.setCursor(12, 1);
    lcd.print("NORM");
  }
  else if(h >= 60){
    lcd.setCursor(12, 1);
    lcd.print(" MAX");
  }
}

void setTempOnDisplay(int h){
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.setCursor(16-String(h).length(), 0);
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
//lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ill-tion:  ");
  lcd.setCursor(16-String(h).length(), 0);
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
//lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SoilHum-ty: ");
  lcd.setCursor(16-String(h).length(), 0);
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