void Welcome(){
  //  Welcome
  lcd.clear();

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