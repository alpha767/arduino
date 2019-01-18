#include <LiquidCrystal_I2C.h>


/*
 *  ************************
 *  test de l'afficheur LCD
 *  
 *  ************************************
 *  convertisseur d eniveau I2C
 *  
 *  Le NodeMcu fonctionne sous 3.3V.
 *  L'afficheur fonctoinne sous 5v
 */



 #include <Wire.h>
 #include <LiquidCrystal_I2C.h>

 LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
 {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Bonjour ALPHA!!!");
  lcd.setCursor(0,1);
  lcd.print("The power of dev");
  
  }

  void loop()
  {
  }
  
