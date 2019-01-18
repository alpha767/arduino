/* 
 * *************************
 * Capteur : DHT11
 * 
 * Les broches sont numérotées de la gauche vers la droite lorsque l'on regarde le capteur de face
 * 
 * Broche n°1 connectée au +3.3V
 * Broche n°2 (data) connectée à la broche 'D4' du NodeMcu (Pin 2 pour l'arduino) avec une résistance de 10 K reliée au +3.3v
 * Broche n°3 non connectée
 * Broche n°4 connectée à la masse (GND)
 * 
 * Installer la bibliothèque 'DHT sensor library by Adarftuit'
 * Cette librairie necessite une librairie supplémentaire qui est disponible à l'adresse : https://github.com/adafruit/Adafruit_Sensor
 * et qui doit être installée selon ce tutoriel : https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/installing-a-library-on-linux
 *  
 */

// Déclaration des librairies
#include <DHT.h>                      // pour communiquer avec le capteur DHT

 #include <Wire.h>
 #include <LiquidCrystal_I2C.h>

 LiquidCrystal_I2C lcd(0x27,16,2);

// Préparation du capteur DHT
#define DHTPIN 2                      // broche sur laquelle est raccordée la data du capteur (la broche 'D4' du NodeMcu correspond à la broche 2 de l'arduino)
#define DHTTYPE DHT11                 // précise la référence du capteur DHT (DHT11 ou DHT21 ou DHT22)
DHT dht(DHTPIN, DHTTYPE); // Initialisation du capteur DHT

// fonction de démarrage
void setup() {
  Serial.begin(115200);
  // Démarrage du bus série
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Humidite: ");
  lcd.setCursor(0,1);
  lcd.print("Temperat:");          // écriture d'un petit message...
  lcd.setCursor(15,1);
  lcd.print("C");
  lcd.setCursor(15,0);
  lcd.println("%");
  // Démarrage du capteur DHT11
  dht.begin();
}

// boucle infinie
void loop() {
  delay(5000);                        // attendre 5 seconde 

  float t = dht.readTemperature();// mesurer la température (en ° Celsius)
  float h = dht.readHumidity();
  
  // test si des valeurs ont été récupérées
  if (isnan(t) || isnan(h)) {   // si non
    
    Serial.println("Failed to read from DHT sensor!");    // affiche un message d'erreur
    return;                           // quitte pour retenter une lecture
  }

  // affichage des valeurs dans le bus série
  //Serial.setCursor(10,1);
  Serial.println("temp="+String(t)+"  hum="+String(h));
  //lcd.setCursor(10,1);
  //Serial.print(h);
  
  lcd.setCursor(10,1);
  lcd.print(t);
  lcd.setCursor(10,0);
  lcd.print(h);
 
}
