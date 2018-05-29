//  Greeting
void Welcome(){
  //  Greeting
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("GreenHouse 2.0");

  delay(3500);

  //  Author
  lcd.setCursor(0, 0);
  lcd.print("Author: ");
  lcd.setCursor(6, 1);
  lcd.print("Шенягин Д.");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("Co-Author: ");
  lcd.setCursor(5, 1);
  lcd.print("Субботин А.");

  delay(3500);

  //  Scientific director
  lcd.setCursor(0, 0);
  lcd.print("Scientific director: ");
  lcd.setCursor(6, 1);
  lcd.print("Краев Н.В.");
}
